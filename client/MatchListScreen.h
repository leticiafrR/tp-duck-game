#ifndef MATCH_LIST_SCREEN_H
#define MATCH_LIST_SCREEN_H

#include <list>
#include <memory>
#include <string>
#include <vector>

#include "data/networkMsg.h"
#include "tweening/ImageTween.h"
#include "tweening/TweenManager.h"

#include "Button.h"
#include "ButtonsManager.h"
#include "Camera.h"
#include "ColorExtension.h"
#include "GUIManager.h"
#include "Image.h"
#include "LoadingScreen.h"
#include "LobbyItemWidget.h"
#include "Rate.h"
#include "SDLExtension.h"
#include "Text.h"

using std::list;
using std::shared_ptr;
using std::string;
using std::vector;

class MatchListScreen {
private:
    Camera& cam;
    Rate rate;
    Client& client;
    list<LobbyItemWidget> widgets;

    float currentY = 0;
    float scrollSize = 0;

    bool running = false;
    bool isOwner = false;

public:
    MatchListScreen(Camera& cam, const Rate& rate, Client& client):
            cam(cam), rate(rate), client(client) {}

    void LoadWidgetList(std::vector<DataMatch> data) {
        widgets.clear();

        Vector2D initialPos(0, -400);
        int moveDelta = 130;

        for (size_t i = 0; i < data.size(); i++) {
            auto lobbyData = data[i];
            widgets.emplace_back(lobbyData.matchID, lobbyData.creatorNickname,
                                 lobbyData.currentPlayers, lobbyData.maxPlayers, [this](int id) {
                                     AudioManager::GetInstance().PlayButtonSFX();

                                     bool joinSuccess;
                                     client.SelectMatch(id);
                                     LoadingScreen loading(cam, rate, [this, &joinSuccess]() {
                                         std::shared_ptr<ResultJoining> joinResult = nullptr;
                                         if (GetServerMsg(client, joinResult)) {
                                             joinSuccess = joinResult->joined;
                                             return true;
                                         }
                                         return false;
                                     });
                                     loading.Render("Creating match");

                                     if (joinSuccess) {
                                         isOwner = false;
                                         running = false;
                                     }
                                 });

            widgets.back().MoveContent(Vector2D::Down() * i * moveDelta + initialPos);
        }

        scrollSize = 400 + data.size() * 130;
    }

    void UpdateWidgetListPosition(Vector2D movement) {

        if (currentY + movement.y > scrollSize - 900 || currentY + movement.y < -20) {
            return;
        }
        currentY += movement.y;
        for (auto& widget: widgets) {
            widget.MoveContent(movement);
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

    bool Render() {
        running = true;
        Image header(RectTransform(Vector2D(0, 0), Vector2D(2200, 300), Vector2D(0.5, 1),
                                   Vector2D(0.5, 1)),
                     ColorExtension::Black(), 3);

        Text titleText("CREATE A LOBBY", 30,
                       RectTransform(Vector2D(0, -50), Vector2D(500, 160), Vector2D(0.5, 1),
                                     Vector2D(0.5, 0.5)),
                       ColorExtension::White(), 4);

        Button createButton(
                RectTransform(Vector2D(0, -130), Vector2D(250, 80), Vector2D(0.5, 1),
                              Vector2D(0.5, 0.5)),
                [this]() {
                    bool joinSuccess;
                    client.CreateMatch();
                    std::cout << "Create match!\n";
                    LoadingScreen loading(cam, rate, [this, &joinSuccess]() {
                        std::shared_ptr<ResultJoining> joinResult = nullptr;
                        if (GetServerMsg(client, joinResult)) {
                            joinSuccess = joinResult->joined;
                            return true;
                        }
                        return false;
                    });
                    loading.Render("Creating match");

                    if (joinSuccess) {
                        isOwner = true;
                        running = false;
                    }
                },
                Color(40, 40, 40), 4);

        Text createButtonText("CREATE", 20,
                              RectTransform(Vector2D(0, -130), Vector2D(250, 80), Vector2D(0.5, 1),
                                            Vector2D(0.5, 0.5)),
                              ColorExtension::White(), 5);

        Text joinLobbyText("OR JOIN A LOBBY", 30,
                           RectTransform(Vector2D(-180, -240), Vector2D(500, 160), Vector2D(0.5, 1),
                                         Vector2D(0.5, 0.5)),
                           ColorExtension::White(), 4);

        Button refreshButton(
                RectTransform(Vector2D(180, -240), Vector2D(250, 80), Vector2D(0.5, 1),
                              Vector2D(0.5, 0.5)),
                [this, &refreshButton]() {
                    AudioManager::GetInstance().PlayButtonSFX();
                    refreshButton.SetInteractable(false);
                    client.Refresh();

                    LoadingScreen loading(cam, rate, [this]() {
                        std::shared_ptr<AvailableMatches> lobbyListResult = nullptr;
                        if (GetServerMsg(client, lobbyListResult)) {
                            LoadWidgetList(lobbyListResult->matches);
                            return true;
                        }
                        return false;
                    });
                    loading.Render("Getting available lobbies");
                    refreshButton.SetInteractable(true);
                },
                Color(40, 40, 40), 4);

        Text refreshButtonText("REFRESH", 20,
                               RectTransform(Vector2D(180, -240), Vector2D(250, 80),
                                             Vector2D(0.5, 1), Vector2D(0.5, 0.5)),
                               ColorExtension::White(), 5);

        // Load the first available lobbies
        LoadingScreen loading(cam, rate, [this]() {
            std::shared_ptr<AvailableMatches> lobbyListResult = nullptr;
            if (GetServerMsg(client, lobbyListResult)) {
                LoadWidgetList(lobbyListResult->matches);
                return true;
            }
            return false;
        });
        loading.Render("Getting available lobbies");

        while (running) {
            cam.Clean();
            SDL_Event event;

            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        exit(0);
                        break;
                    case SDL_MOUSEWHEEL:
                        Vector2D wheelDir = Vector2D::Down() * event.wheel.y;
                        UpdateWidgetListPosition(wheelDir * rate.GetDeltaTime() * 2500);
                        break;
                }

                ButtonsManager::GetInstance().HandleEvent(event, cam);
            }

            GUIManager::GetInstance().Draw(cam);
            TweenManager::GetInstance().Update(rate.GetDeltaTime());

            cam.Render();
            SDL_Delay(rate.GetMiliseconds());
        }

        return isOwner;
    }

    ~MatchListScreen() = default;
};

#endif
