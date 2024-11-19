#ifndef LOBBY_SCREEN_H
#define LOBBY_SCREEN_H
#include <memory>

#include "data/networkMsg.h"
#include "network/Client.h"
#include "tweening/TweenManager.h"

#include "ButtonsManager.h"
#include "Camera.h"
#include "ColorExtension.h"
#include "GUIManager.h"
#include "LoadingScreen.h"
#include "Rate.h"
#include "Text.h"

using std::shared_ptr;

class LobbyScreen {
private:
    Camera& cam;
    Rate rate;
    Client& client;
    bool isOwner;

    bool running = false;
    bool waitingToStart = false;

public:
    LobbyScreen(Camera& cam, const Rate& rate, Client& client, bool isOwner):
            cam(cam), rate(rate), client(client), isOwner(isOwner) {}

    template <typename NetworkMsgDerivedClass>
    bool GetServerMsg(Client& client, std::shared_ptr<NetworkMsgDerivedClass>& concretPtr) {
        shared_ptr<NetworkMsg> msg;
        if (client.TryRecvNetworkMsg(msg)) {
            concretPtr = dynamic_pointer_cast<NetworkMsgDerivedClass>(msg);
            return true;
        }
        return false;
    }

    std::shared_ptr<MatchStartDto> Render() {
        running = true;
        Button startButton(
                RectTransform(Vector2D(0, -130), Vector2D(250, 80), Vector2D(0.5, 1),
                              Vector2D(0.5, 0.5)),
                [this, &startButton]() {
                    AudioManager::GetInstance().PlayButtonSFX();

                    client.StartMatch();
                    bool startSuccess;
                    startButton.SetInteractable(false);
                    std::cout << "Start match!\n";
                    LoadingScreen loading(cam, rate, [this, &startSuccess]() {
                        std::shared_ptr<ResultJoining> joinResult = nullptr;
                        if (GetServerMsg(client, joinResult)) {
                            startSuccess = joinResult->joined;
                            return true;
                        }
                        return false;
                    });
                    loading.Render("Waiting for server", true);

                    if (!startSuccess) {
                        startButton.SetInteractable(true);
                    } else {
                        waitingToStart = true;
                    }
                },
                Color(40, 40, 40), 4);

        Text startButtonText("START", 20,
                             RectTransform(Vector2D(0, -130), Vector2D(250, 80), Vector2D(0.5, 1),
                                           Vector2D(0.5, 0.5)),
                             ColorExtension::White(), 5);

        Text waitingTest("Waiting the host to start the match", 45,
                         RectTransform(Vector2D(0, 0), Vector2D(800, 150), Vector2D(0.5, 0.5),
                                       Vector2D(0.5, 0.5)),
                         ColorExtension::White(), 5);

        if (!isOwner) {
            waitingToStart = true;
            startButton.SetVisible(false);
            startButtonText.SetVisible(false);
        }

        waitingTest.SetVisible(!isOwner);

        while (running) {
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

            if (waitingToStart) {
                std::shared_ptr<MatchStartDto> matchStart = nullptr;
                if (GetServerMsg(client, matchStart)) {
                    return matchStart;
                }
            }

            GUIManager::GetInstance().Draw(cam);
            TweenManager::GetInstance().Update(rate.GetDeltaTime());

            cam.Render();
            SDL_Delay(rate.GetMiliseconds());
        }
        return nullptr;
    }

    ~LobbyScreen() = default;
};

#endif
