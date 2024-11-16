#ifndef MATCH_LIST_SCREEN_H
#define MATCH_LIST_SCREEN_H

#include <list>
#include <string>
#include <vector>

#include "tweening/ImageTween.h"
#include "tweening/TweenManager.h"

#include "Button.h"
#include "ButtonsManager.h"
#include "Camera.h"
#include "ColorExtension.h"
#include "GUIManager.h"
#include "Image.h"
#include "LobbyItemWidget.h"
#include "Rate.h"
#include "SDLExtension.h"
#include "Text.h"

using std::list;
using std::string;
using std::vector;

// Testing data
struct LobbyDataDummy {
    string owner;
    int playerCount;
    int maxPlayers;
};

class MatchListScreen {
private:
    Camera& cam;
    Rate rate;
    list<LobbyItemWidget> widgets;

    float currentY = 0;
    float scrollSize = 0;

public:
    MatchListScreen(Camera& cam, const Rate& rate): cam(cam), rate(rate) {}

    void LoadWidgetList(vector<LobbyDataDummy> data) {
        widgets.clear();

        Vector2D initialPos(0, -300);
        int moveDelta = 130;

        for (size_t i = 0; i < data.size(); i++) {
            auto lobbyData = data[i];
            widgets.emplace_back(lobbyData.owner, lobbyData.playerCount, lobbyData.maxPlayers,
                                 []() {});

            widgets.back().MoveContent(Vector2D::Down() * i * moveDelta + initialPos);
        }

        scrollSize = (data.size() + 1) * 130;
    }

    void UpdateWidgetListPosition(Vector2D movement) {

        if (currentY + movement.y > scrollSize - 800 || currentY + movement.y < -20) {
            return;
        }
        currentY += movement.y;
        for (auto& widget: widgets) {
            widget.MoveContent(movement);
        }
    }

    void Render() {
        bool running = true;

        Image header(RectTransform(Vector2D(0, 0), Vector2D(2200, 200), Vector2D(0.5, 1),
                                   Vector2D(0.5, 1)),
                     ColorExtension::Black(), 3);

        Text titleText("SELECT OR CREATE A LOBBY", 160,
                       RectTransform(Vector2D(0, -50), Vector2D(500, 160), Vector2D(0.5, 1),
                                     Vector2D(0.5, 0.5)),
                       ColorExtension::White(), 4);

        Button createButton(
                RectTransform(Vector2D(0, -150), Vector2D(320, 80), Vector2D(0.5, 1),
                              Vector2D(0.5, 0.5)),
                [&running]() { running = false; }, Color(40, 40, 40), 4);

        Text createButtonText("CREATE MATCH", 30,
                              RectTransform(Vector2D(0, -150), Vector2D(320, 80), Vector2D(0.5, 1),
                                            Vector2D(0.5, 0.5)),
                              ColorExtension::White(), 5);

        LoadWidgetList(vector<LobbyDataDummy>{
                LobbyDataDummy{"josValentin", 2, 5},
                LobbyDataDummy{"metalica", 4, 5},
                LobbyDataDummy{"andrew garfield", 3, 5},
                LobbyDataDummy{"antuaned garfield", 4, 5},
                LobbyDataDummy{"random", 4, 5},
                LobbyDataDummy{"random", 4, 5},
                LobbyDataDummy{"random", 4, 5},
                LobbyDataDummy{"random", 4, 5},
                LobbyDataDummy{"random", 4, 5},
                LobbyDataDummy{"random", 4, 5},
        });

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
    }

    ~MatchListScreen() = default;
};

#endif
