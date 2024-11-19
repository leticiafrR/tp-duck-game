#include <exception>
#include <iostream>
#include <map>
#include <set>
#include <thread>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/SDLTTF.hh>

#include "common/Collision.h"
#include "common/RigidBody.h"
#include "data/command.h"
#include "data/dataTransferObjects.h"
#include "data/gameScene.h"
#include "data/networkMsg.h"
#include "data/snapshot.h"
#include "network/Client.h"
#include "tweening/ImageTween.h"
#include "tweening/TweenManager.h"

#include "Animator.h"
#include "AudioManager.h"
#include "BulletRenderer.h"
#include "Button.h"
#include "ButtonsManager.h"
#include "Camera.h"
#include "CameraController.h"
#include "ColorExtension.h"
#include "DuckClientRenderer.h"
#include "GUIManager.h"
#include "Gameplay.h"
#include "Image.h"
#include "LoadingScreen.h"
#include "LobbyScreen.h"
#include "MapBlock2D.h"
#include "MatchListScreen.h"
#include "MenuScreen.h"
#include "Object2D.h"
#include "Rate.h"
#include "SheetDataCache.h"
#include "Text.h"

using namespace SDL2pp;  // NOLINT
using namespace std;     // NOLINT

void ShowWinner(Camera& cam, Client& client, const Rate& rate, vector<PlayerData> players) {
    // bool running = true;

    Text winnerText("GETTING WINNER...", 160,
                    RectTransform(Transform(Vector2D(0, 30), Vector2D(500, 160)),
                                  Vector2D(0.5, 0.5), Vector2D(0.5, 0.5)),
                    ColorExtension::White());

    while (true) {
        cam.Clean();
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit(0);
                    break;
            }
            ButtonsManager::GetInstance().HandleEvent(event, cam);
        }

        shared_ptr<NetworkMsg> msg;
        if (client.TryRecvNetworkMsg(msg)) {
            auto matchEnded = dynamic_pointer_cast<FinalWinner>(msg);

            auto it = std::find_if(players.begin(), players.end(), [&matchEnded](PlayerData p) {
                return p.playerID == matchEnded->winner;
            });

            if (it != players.end())
                winnerText.SetText("The winner is: " + it->nickname);
            else
                winnerText.SetText("There is no winner");
        }

        GUIManager::GetInstance().Draw(cam);
        cam.Render();
        SDL_Delay(rate.GetMiliseconds());
    }
}

int main() try {
    // Initialization
    SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDLMixer sdlMixer(MIX_INIT_MP3 | MIX_INIT_OGG);
    AudioManager::GetInstance();
    SDLTTF ttf;

    Window window("Duck Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 940, 940,
                  SDL_WINDOW_RESIZABLE);
    Renderer render(window, -1, SDL_RENDERER_ACCELERATED);
    render.SetDrawBlendMode(SDL_BlendMode::SDL_BLENDMODE_BLEND);  // Allows transparency
    render.SetDrawColor(100, 100, 100, 255);

    Camera cam(std::move(render), 70);
    Rate rate(90);
    // TestMain(cam);
    string nickname = MenuScreen(cam, rate).Render();

    Client client("8080", "localhost", nickname);
    bool isOwner = MatchListScreen(cam, rate, client).Render();

    std::shared_ptr<MatchStartDto> playerData = LobbyScreen(cam, rate, client, isOwner).Render();

    bool matchEnded = false;

    while (!matchEnded) {
        std::shared_ptr<GameSceneDto> mapData = nullptr;
        std::shared_ptr<Snapshot> firstSnapshot = nullptr;

        LoadingScreen loadingRoundScreen(cam, rate, [&client, &mapData, &firstSnapshot]() {
            if (!mapData)
                client.TryRecvNetworkMsg(mapData);
            if (mapData && !firstSnapshot)
                client.TryRecvNetworkMsg(firstSnapshot);
            return mapData && firstSnapshot;
        });
        loadingRoundScreen.Render("LOADING...");

        Gameplay(client, cam, rate, *playerData, *mapData, *firstSnapshot).Run();

        bool isFinalGroup = false;
        while (!isFinalGroup) {
            mapData = nullptr;
            firstSnapshot = nullptr;
            loadingRoundScreen.Render("LOADING...");
            Gameplay(client, cam, rate, *playerData, *mapData, *firstSnapshot).Run();

            LoadingScreen loadingFinalGroup(cam, rate, [&isFinalGroup, &client]() {
                std::shared_ptr<FinalGroupGame> finalGroupData;

                if (client.TryRecvNetworkMsg(finalGroupData)) {
                    isFinalGroup = finalGroupData->finalGroupGame;
                    return true;
                }
                return false;
            });
            loadingFinalGroup.Render("LOADING...");
        }

        LoadingScreen matchEndedScreen(cam, rate, [&client, &matchEnded]() {
            std::shared_ptr<GamesRecountDto> recountData;
            if (client.TryRecvNetworkMsg(recountData)) {
                matchEnded = recountData->matchEnded;
                return true;
            }
            return false;
        });
        matchEndedScreen.Render("GETTING RESULTS");
    }

    ShowWinner(cam, client, rate, playerData->playersData);

    FontCache::Clear();
    SheetDataCache::Clear();
    //  Here all resources are automatically released and library deinitialized
    return 0;
} catch (std::exception& e) {
    // If case of error, print it and exit with error
    std::cerr << e.what() << std::endl;
    return 1;
}
