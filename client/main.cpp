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

#include "Animator.h"
#include "BulletRenderer.h"
#include "Button.h"
#include "ButtonsManager.h"
#include "Camera.h"
#include "CameraController.h"
#include "ColorExtension.h"
#include "DuckClientRenderer.h"
#include "LoadingScreen.h"
#include "MapBlock2D.h"
#include "MatchListScreen.h"
#include "MenuScreen.h"
#include "Object2D.h"
#include "Rate.h"
#include "SheetDataCache.h"
#include "Text.h"
using namespace SDL2pp;  // NOLINT
using namespace std;     // NOLINT


void TestMain(Camera& cam) {
    Object2D bgSpr("bg_forest.png", Transform(Vector2D::Zero(), Vector2D(200, 200)));

    Object2D spr("base_duck.png", Transform(Vector2D::Zero(), Vector2D(5, 5)));

    Object2D akSpr("machine_guns.png", Transform(Vector2D::Zero(), Vector2D(4, 4)));
    akSpr.SetSourceRect(SheetDataCache::GetData("machine_guns.yaml")["ak_47"][0]);

    Animator duckAnim(spr, "duck.yaml", "idle", 17);

    MapBlock2D mapBlock("tile_set.png", "tile_set.yaml",
                        Transform(Vector2D(0, -10), Vector2D(40, 20)), 5);

    mapBlock.SetBorders(true, true, true, true);

    spr.SetColor(Color(255, 255, 255));

    Transform& duckT = spr.GetTransform();
    RigidBody rb(duckT, 8);
    Transform& platformT = mapBlock.transform;

    CameraController camController(cam);
    camController.AddTransform(&duckT);
    camController.AddTransform(&platformT);

    std::set<int> pressedKeysSet;
    bool running = true;
    Vector2D dir = Vector2D::Zero();

    int fps = 60;
    float sleepMS = 1000.0f / fps;
    float deltaTime = 1.0f / fps;
    float speed = 15;
    bool isGrounded = false;

    while (running) {
        cam.Clean();
        SDL_Event event;
        duckAnim.SetTarget("idle", false);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN: {
                    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;

                    int key = keyEvent.keysym.sym;
                    if (pressedKeysSet.find(key) != pressedKeysSet.end()) {
                        break;
                    }
                    pressedKeysSet.insert(key);

                    switch (keyEvent.keysym.sym) {
                        case SDLK_a:
                            dir += Vector2D::Left();
                            break;
                        case SDLK_d:
                            dir += Vector2D::Right();
                            break;
                        case SDLK_SPACE:
                            if (isGrounded) {
                                rb.ApplyForce(Vector2D::Up() * 40);
                            }
                            break;
                    }
                } break;
                case SDL_KEYUP: {
                    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
                    int key = keyEvent.keysym.sym;
                    pressedKeysSet.erase(key);

                    switch (keyEvent.keysym.sym) {
                        case SDLK_a:
                            spr.SetFlip(true);
                            dir += Vector2D::Left() * -1;
                            break;
                        case SDLK_d:
                            spr.SetFlip(false);
                            dir += Vector2D::Right() * -1;
                            break;
                    }
                    break;
                }
                case SDL_MOUSEMOTION:
                    // std::cout << "Oh! Mouse" << std::endl;
                    break;
                case SDL_QUIT:
                    running = false;
                    break;
            }
            // ButtonsManager::GetInstance().HandleEvent(event);
        }
        duckT.Move(dir * speed * deltaTime);

        if (dir.GetMagnitude() > 0.001) {
            duckAnim.SetTarget("run", false);
        } else {
            duckAnim.SetTarget("idle");
        }

        duckAnim.Update(deltaTime);

        if (dir.x > 0)
            spr.SetFlip(false);
        else if (dir.x < 0)
            spr.SetFlip(true);

        rb.Update(deltaTime);

        isGrounded = Collision::Raycast(duckT.GetPos(), Vector2D::Down(), 4, platformT);
        if (Collision::RectCollision(duckT, platformT)) {
            Collision::ResolveStaticCollision(duckT, platformT);
            if (isGrounded) {
                rb.ResetGravity();
            }
        }

        bgSpr.Draw(cam);
        mapBlock.Draw(cam);
        spr.Draw(cam);

        akSpr.GetTransform().SetPos(duckT.GetPos() + Vector2D::Down() * 0.8f);
        akSpr.SetFlip(spr.GetFlip());
        akSpr.Draw(cam);

        // ButtonsManager::GetInstance().Draw(cam);

        camController.Update();
        cam.Render();
        SDL_Delay(sleepMS);
    }
}

void Connecting(Camera& cam, Client& client, const Rate& rate) {
    bool running = true;

    Text titleText("CONNECTING TO SEVER...", 160,
                   RectTransform(Transform(Vector2D(0, 30), Vector2D(500, 160)), Vector2D(0.5, 0.5),
                                 Vector2D(0.5, 0.5)),
                   ColorExtension::White());

    while (running) {
        cam.Clean();
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit(0);
                    break;
            }
        }

        shared_ptr<NetworkMsg> msg;
        if (client.TryRecvNetworkMsg(msg)) {
            auto joined = dynamic_pointer_cast<ResultJoining>(msg);
            if (joined)
                running = false;  // Enter to the match
        }

        titleText.Draw(cam);
        cam.Render();
        SDL_Delay(rate.GetMiliseconds());
    }
}

shared_ptr<MatchStartDto> LoadingPlayers(Camera& cam, Client& client, Rate rate) {

    Text titleText("LOADING PLAYERS DATA...", 160,
                   RectTransform(Transform(Vector2D(0, 30), Vector2D(500, 160)), Vector2D(0.5, 0.5),
                                 Vector2D(0.5, 0.5)),
                   ColorExtension::White());

    while (true) {
        cam.Clean();
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit(0);
                    // running = false;
                    break;
            }
        }

        shared_ptr<NetworkMsg> msg;
        if (client.TryRecvNetworkMsg(msg)) {
            auto matchData = dynamic_pointer_cast<MatchStartDto>(msg);
            return matchData;
        }

        titleText.Draw(cam);
        cam.Render();
        SDL_Delay(rate.GetMiliseconds());
    }
    return nullptr;
}

bool IsFinalGroupGame(Camera& cam, Client& client, const Rate& rate) {
    Text titleText("PROCESSING ROUND...", 160,
                   RectTransform(Transform(Vector2D(0, 30), Vector2D(500, 160)), Vector2D(0.5, 0.5),
                                 Vector2D(0.5, 0.5)),
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
            auto finalGroupData = dynamic_pointer_cast<FinalGroupGame>(msg);
            return finalGroupData->finalGroupGame;
            // running = false;  // Go to game and snapshots
        }

        GUIManager::GetInstance().Draw(cam);
        cam.Render();
        SDL_Delay(rate.GetMiliseconds());
    }
    return false;
}

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

void Game(Camera& cam, Client& client, const Rate& rate, MatchStartDto matchData,
          GameSceneDto mapData, Snapshot firstSnapshot) {

    CameraController camController(cam);
    // Set Players
    map<PlayerID_t, std::shared_ptr<DuckClientRenderer>> players;

    for (auto& playerData: matchData.playersData) {
        if (firstSnapshot.updates.find(playerData.playerID) == firstSnapshot.updates.end())
            continue;
        Vector2D spawnPos = firstSnapshot.updates[playerData.playerID].motion;
        players.emplace(playerData.playerID,
                        std::make_shared<DuckClientRenderer>(
                                Transform(spawnPos, matchData.duckSize), playerData.playerSkin));

        camController.AddTransform(&players.at(playerData.playerID)->GetTransform());
    }

    // Set Map
    vector<MapBlock2D> mapBlocks;

    for (size_t i = 0; i < mapData.groundBlocks.size(); i++) {
        auto groundData = mapData.groundBlocks[i];
        mapBlocks.emplace_back("tile_set.png", "tile_set.yaml", groundData.mySpace, 5);

        bool left =
                groundData.visibleEdges.find(VISIBLE_EDGES::LEFT) != groundData.visibleEdges.end();
        bool right =
                groundData.visibleEdges.find(VISIBLE_EDGES::RIGHT) != groundData.visibleEdges.end();
        bool top =
                groundData.visibleEdges.find(VISIBLE_EDGES::TOP) != groundData.visibleEdges.end();
        bool bottom = groundData.visibleEdges.find(VISIBLE_EDGES::BOTTOM) !=
                      groundData.visibleEdges.end();

        mapBlocks[i].SetBorders(left, right, top, bottom);
    }

    // Gameloop
    std::set<int> pressedKeysSet;

    Object2D bgSpr("bg_forest.png", Transform(Vector2D::Zero(), Vector2D(200, 200)));

    bool running = true;

    std::vector<shared_ptr<BulletRenderer>> bullets;

    while (running) {
        cam.Clean();
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN: {
                    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;

                    int key = keyEvent.keysym.sym;
                    if (pressedKeysSet.find(key) != pressedKeysSet.end()) {
                        break;
                    }
                    pressedKeysSet.insert(key);

                    switch (keyEvent.keysym.sym) {
                        case SDLK_a:
                            client.TrySendRequest(CommandCode::MoveLeft_KeyDown);
                            break;
                        case SDLK_d:
                            client.TrySendRequest(CommandCode::MoveRight_KeyDown);
                            break;
                        case SDLK_SPACE:
                            client.TrySendRequest(CommandCode::Jump);
                            break;
                        case SDLK_r:
                            client.TrySendRequest(CommandCode::UseItem_KeyDown);
                            break;
                    }
                } break;
                case SDL_KEYUP: {
                    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
                    int key = keyEvent.keysym.sym;
                    pressedKeysSet.erase(key);

                    switch (keyEvent.keysym.sym) {
                        case SDLK_a:
                            client.TrySendRequest(CommandCode::MoveLeft_KeyUp);
                            break;
                        case SDLK_d:
                            client.TrySendRequest(CommandCode::MoveRight_KeyUp);
                            break;
                    }
                    break;
                }
                case SDL_QUIT:
                    exit(0);
                    // running = false;
                    break;
            }
            // ButtonsManager::GetInstance().HandleEvent(event);
        }

        shared_ptr<NetworkMsg> msg;
        if (client.TryRecvNetworkMsg(msg)) {
            Snapshot snapshot = *dynamic_pointer_cast<Snapshot>(msg);
            for (size_t i = 0; i < snapshot.raycastsEvents.size(); i++) {
                auto ray = snapshot.raycastsEvents[i];
                bullets.emplace_back(std::make_shared<BulletRenderer>(ray.origin, ray.end, 70));
            }

            for (const auto& it: snapshot.updates) {
                players[it.first]->SetEventTarget(it.second);
            }
            // Check if last snapshot...
            if (snapshot.gameOver) {
                running = false;
            }
        }

        // Rendering

        bgSpr.Draw(cam);

        for (auto& it: mapBlocks) {
            it.Draw(cam);
        }

        for (auto& it: bullets) {
            it->Update(rate.GetDeltaTime());
            it->Draw(cam);
        }

        for (const auto& it: players) {
            auto data = it.second;
            data->Update(rate.GetDeltaTime());
            data->Draw(cam);
        }

        GUIManager::GetInstance().Draw(cam);

        camController.Update();
        cam.Render();
        SDL_Delay(rate.GetMiliseconds());
    }
}

template <typename NetworkMsgDerivedClass>
bool GetServerMsg(Client& client, std::shared_ptr<NetworkMsgDerivedClass>& concretPtr) {
    shared_ptr<NetworkMsg> msg;
    if (client.TryRecvNetworkMsg(msg)) {
        concretPtr = dynamic_pointer_cast<NetworkMsgDerivedClass>(msg);
        return true;
    }
    return false;
}

int main() try {
    SDL sdl(SDL_INIT_VIDEO);
    Window window("Duck Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 940, 940,
                  SDL_WINDOW_RESIZABLE);
    Renderer render(window, -1, SDL_RENDERER_ACCELERATED);
    render.SetDrawColor(100, 100, 100, 255);
    SDLTTF ttf;

    Camera cam(std::move(render), 70);
    Rate rate(60);
    // TestMain(cam);
    string nickname = MenuScreen(cam, rate).Render();
    MatchListScreen(cam, rate).Render();

    Client client("8080", "localhost", nickname);
    Connecting(cam, client, rate);
    auto playerData = LoadingPlayers(cam, client, rate);

    bool matchEnded = false;

    while (!matchEnded) {
        std::shared_ptr<GameSceneDto> mapData = nullptr;
        std::shared_ptr<Snapshot> firstSnapshot = nullptr;

        LoadingScreen loadingRoundScreen(cam, rate, [&client, &mapData, &firstSnapshot]() {
            if (!mapData)
                GetServerMsg(client, mapData);
            if (mapData && !firstSnapshot)
                GetServerMsg(client, firstSnapshot);
            return mapData && firstSnapshot;
        });
        loadingRoundScreen.Render("LOADING...");

        Game(cam, client, rate, *playerData, *mapData, *firstSnapshot);
        std::cout << "Round ended\n";

        while (!IsFinalGroupGame(cam, client, rate)) {
            mapData = nullptr;
            firstSnapshot = nullptr;
            loadingRoundScreen.Render("LOADING...");
            Game(cam, client, rate, *playerData, *mapData, *firstSnapshot);
            std::cout << "Round ended\n";
        }
        std::cout << "Rounds group ended\n";

        LoadingScreen matchEndedScreen(cam, rate, [&client, &matchEnded]() {
            std::shared_ptr<GamesRecountDto> recountData;
            if (GetServerMsg(client, recountData)) {
                matchEnded = recountData->matchEnded;
                return true;
            }
            return false;
        });
        matchEndedScreen.Render("GETTING RESULTS");

        if (!matchEnded)
            std::cout << "Match is not endend, continue with game\n";
    }
    std::cout << "Match ended \n";
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
