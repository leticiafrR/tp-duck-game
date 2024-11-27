#ifndef MATCH_LIST_SCREEN_H
#define MATCH_LIST_SCREEN_H

#include <list>
#include <memory>
#include <string>
#include <vector>

#include "client/tweening/ImageTween.h"
#include "client/tweening/TweenManager.h"
#include "client/utils/SDLExtension.h"
#include "data/networkMsg.h"
#include "multimedia/Button.h"
#include "multimedia/ButtonsManager.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/GUIManager.h"
#include "multimedia/Image.h"
#include "multimedia/Text.h"

#include "ControlsScreen.h"
#include "LoadingScreen.h"
#include "LobbyItemWidget.h"
#include "PlayersCountSelection.h"

using std::list;
using std::shared_ptr;
using std::string;
using std::vector;

class MatchListScreen {
private:
    Camera& cam;
    Client& client;
    list<LobbyItemWidget> widgets;

    float currentY = 0;
    float scrollSize = 0;

    bool running = false;
    bool isOwner = false;

    Image header;
    Text titleText;

    Button createButton;
    Text createButtonText;

    Text joinLobbyText;

    Button refreshButton;
    Text refreshButtonText;

    Button controlsButton;
    Text controlsButtonText;

    ControlsScreen controls;

    PlayersCountSelection playersCountSelection;

    void OnCreatePressed() {
        AudioManager::GetInstance().PlayButtonSFX();

        playersCountSelection.Display([this](uint8_t playersCount) {
            bool createSuccess;
            client.CreateMatch(playersCount);
            LoadingScreen loading(cam, [this, &createSuccess]() {
                std::shared_ptr<ResultJoining> joinResult = nullptr;
                if (client.TryRecvNetworkMsg(joinResult)) {
                    createSuccess = joinResult->eCode == 0;
                    return true;
                }
                return false;
            });
            loading.Run("Creating match");

            if (createSuccess) {
                isOwner = true;
                running = false;
            }
        });
    }

    void OnJoinLobbyPressed(int id) {
        AudioManager::GetInstance().PlayButtonSFX();

        playersCountSelection.Display([this, id](uint8_t playersCount) {
            bool joinSuccess;
            client.SelectMatch(id, playersCount);
            LoadingScreen loading(cam, [this, &joinSuccess]() {
                std::shared_ptr<ResultJoining> joinResult = nullptr;
                if (client.TryRecvNetworkMsg(joinResult)) {
                    joinSuccess = joinResult->eCode == 0;
                    return true;
                }
                return false;
            });
            loading.Run("Joining match");

            if (joinSuccess) {
                isOwner = false;
                running = false;
            }
        });
    }

    void OnRefreshPressed() {
        AudioManager::GetInstance().PlayButtonSFX();
        refreshButton.SetInteractable(false);
        client.Refresh();
        WaitRefresh();
        refreshButton.SetInteractable(true);
    }

    void WaitRefresh() {
        LoadingScreen loading(cam, [this]() {
            std::shared_ptr<AvailableMatches> lobbyListResult = nullptr;
            if (client.TryRecvNetworkMsg(lobbyListResult)) {
                LoadWidgetList(lobbyListResult->matches);
                return true;
            }
            return false;
        });
        loading.Run("Getting available lobbies");
    }

    void LoadWidgetList(std::vector<DataMatch> data) {
        widgets.clear();

        Vector2D initialPos(0, -400);
        int moveDelta = 130;

        for (size_t i = 0; i < data.size(); i++) {
            auto lobbyData = data[i];
            widgets.emplace_back(lobbyData.matchID, lobbyData.creatorNickname,
                                 lobbyData.currentPlayers, lobbyData.maxPlayers,
                                 [this](int id) { this->OnJoinLobbyPressed(id); });

            widgets.back().MoveContent(Vector2D::Down() * i * moveDelta + initialPos);
        }

        scrollSize = 400 + data.size() * 130;
        currentY = 0;
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

public:
    MatchListScreen(Camera& c, Client& cl):
            cam(c),
            client(cl),
            header(RectTransform(Vector2D(0, 0), Vector2D(2200, 300), Vector2D(0.5, 1),
                                 Vector2D(0.5, 1)),
                   ColorExtension::Black(), 3),
            titleText("CREATE A LOBBY", 30,
                      RectTransform(Vector2D(0, -50), Vector2D(500, 160), Vector2D(0.5, 1),
                                    Vector2D(0.5, 0.5)),
                      ColorExtension::White(), 4),
            createButton(
                    "button_1.png",
                    RectTransform(Vector2D(0, -130), Vector2D(250, 80), Vector2D(0.5, 1),
                                  Vector2D(0.5, 0.5)),
                    [this]() { this->OnCreatePressed(); }, Color(40, 40, 40), 4),
            createButtonText("CREATE", 20,
                             RectTransform(Vector2D(0, -130), Vector2D(250, 80), Vector2D(0.5, 1),
                                           Vector2D(0.5, 0.5)),
                             ColorExtension::White(), 5),
            joinLobbyText("OR JOIN A LOBBY", 30,
                          RectTransform(Vector2D(-180, -240), Vector2D(500, 160), Vector2D(0.5, 1),
                                        Vector2D(0.5, 0.5)),
                          ColorExtension::White(), 4),
            refreshButton(
                    "button_1.png",
                    RectTransform(Vector2D(180, -240), Vector2D(250, 80), Vector2D(0.5, 1),
                                  Vector2D(0.5, 0.5)),
                    [this]() { this->OnRefreshPressed(); }, Color(40, 40, 40), 4),
            refreshButtonText("REFRESH", 20,
                              RectTransform(Vector2D(180, -240), Vector2D(250, 80),
                                            Vector2D(0.5, 1), Vector2D(0.5, 0.5)),
                              ColorExtension::White(), 5),
            controlsButton(
                    "button_1.png",
                    RectTransform(Vector2D(-85, -45), Vector2D(160, 80), Vector2D(1, 1),
                                  Vector2D(0.5, 0.5)),
                    [this]() {
                        this->controls.SetActive(true);
                        AudioManager::GetInstance().PlayButtonSFX();
                    },
                    Color(40, 40, 40), 4),
            controlsButtonText("CONTROLS", 20,
                               RectTransform(Vector2D(-85, -45), Vector2D(160, 80), Vector2D(1, 1),
                                             Vector2D(0.5, 0.5)),
                               ColorExtension::White(), 5) {
        controls.SetActive(false);
    }

    bool Render() {
        running = true;

        // Get the first available lobbies
        WaitRefresh();

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
                        UpdateWidgetListPosition(wheelDir * cam.GetRateDeltatime() * 2500);
                        break;
                }

                ButtonsManager::GetInstance().HandleEvent(event, cam);
            }

            GUIManager::GetInstance().Draw(cam);
            TweenManager::GetInstance().Update(cam.GetRateDeltatime());

            cam.Render();
            SDL_Delay(cam.GetRateMiliseconds());
        }

        return isOwner;
    }

    ~MatchListScreen() = default;
};

#endif
