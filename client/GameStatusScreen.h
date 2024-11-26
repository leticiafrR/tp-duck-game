#ifndef GAME_STATUS_SCREEN_H
#define GAME_STATUS_SCREEN_H

#include <algorithm>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

#include "data/dataTransferObjects.h"
#include "multimedia/Button.h"
#include "multimedia/ButtonsManager.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/GUIManager.h"
#include "multimedia/Text.h"

#include "DuckClientRenderer.h"
#include "ShowColorsScreen.h"
#include "Timer.h"

using std::make_shared;
using std::shared_ptr;
using std::unordered_map;
using std::vector;

class DuckResultItemGUI {
private:
    Image imgColor;
    Text txtNickname;
    Text txtCount;

public:
    DuckResultItemGUI(Vector2D pos, const PlayerData& duck, int count):
            imgColor("base_duck.png", RectTransform(pos, Vector2D(70, 70)),
                     DuckClientRenderer::GetColorById(duck.playerSkin), 20),
            txtNickname(duck.nickname, 30,
                        RectTransform(Vector2D(pos.x + 50, pos.y), Vector2D(300, 150),
                                      Vector2D(0.5, 0.5), Vector2D(0, 0.5)),
                        ColorExtension::White(), 20),
            txtCount(std::to_string(count), 35,
                     RectTransform(Vector2D(pos.x + 390, pos.y), Vector2D(150, 150),
                                   Vector2D(0.5, 0.5), Vector2D(0, 0.5)),
                     ColorExtension::White(), 20) {

        imgColor.SetSourceRect(SheetDataCache::GetData("duck.yaml")["head"][0]);
    }

    ~DuckResultItemGUI() = default;
};

class GameStatusScreen {
private:
    Camera& cam;
    Image imgBg;
    Text txtTitle;
    Button btnBack;

    vector<shared_ptr<DuckResultItemGUI>> ducksGUI;

    bool running = true;

public:
    GameStatusScreen(Camera& cam, vector<PlayerData> players,
                     unordered_map<PlayerID_t, int> gameResults, std::optional<PlayerData> winner):
            cam(cam),
            imgBg(RectTransform(Vector2D::Zero(), Vector2D(2000, 2000)), ColorExtension::Black()),
            txtTitle("", 40, RectTransform(Vector2D(0, -130), Vector2D(800, 120), Vector2D(0.5, 1)),
                     ColorExtension::White(), 10),
            btnBack(
                    "back_icon.png",
                    RectTransform(Vector2D(60, -60), Vector2D(70, 70), Vector2D(0, 1)),
                    [this]() {
                        running = false;
                        AudioManager::GetInstance().PlayButtonSFX();
                    },
                    ColorExtension::White(), 11) {


        if (winner.has_value()) {
            txtTitle.SetText("The winner is: " + winner.value().nickname);
            btnBack.SetActive(true);
        } else {
            txtTitle.SetText("Game status");
            btnBack.SetActive(false);
        }

        std::sort(players.begin(), players.end(), [&gameResults](PlayerData a, PlayerData b) {
            return gameResults[a.playerID] > gameResults[b.playerID];
        });

        Vector2D initialPos(-200, 100);
        for (const auto& it: players) {
            ducksGUI.emplace_back(
                    std::make_shared<DuckResultItemGUI>(initialPos, it, gameResults[it.playerID]));
            initialPos += Vector2D::Down() * 80;
        }
    }

    void Run() {

        Timer timer(3.0f, [this]() { running = false; });

        if (!btnBack.GetVisible()) {
            timer.Start();
        }

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

            timer.Update(cam.GetRateDeltatime());
            GUIManager::GetInstance().Draw(cam);
            cam.Render();
            SDL_Delay(cam.GetRateMiliseconds());
        }
    }

    ~GameStatusScreen() = default;
};

#endif
