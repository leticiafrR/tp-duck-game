#ifndef SHOW_COLORS_SCREEN_H
#define SHOW_COLORS_SCREEN_H

#include <memory>
#include <vector>

#include "multimedia/ColorExtension.h"
#include "multimedia/Definitions.h"
#include "multimedia/Image.h"
#include "multimedia/Text.h"
#include "tweening/ImageTween.h"
#include "tweening/TweenManager.h"

#include "DuckClientRenderer.h"
#include "Timer.h"

using std::make_shared;
using std::shared_ptr;
using std::vector;

class DuckColorItemGUI {
private:
    Image imgColor;
    Text txtNickname;

public:
    DuckColorItemGUI(Vector2D pos, const DuckClientRenderer& duck):
            imgColor("base_duck.png", RectTransform(pos, Vector2D(70, 70)), duck.GetSkinColor(),
                     20),
            txtNickname(duck.GetNickname(), 35,
                        RectTransform(Vector2D(pos.x + 170, pos.y), Vector2D(150, 150)),
                        ColorExtension::White(), 20) {

        imgColor.SetSourceRect(SheetDataCache::GetData("duck.yaml")["head"][0]);
    }

    ~DuckColorItemGUI() = default;
};


class ShowColorsScreen {
private:
    Camera& cam;

    map<PlayerID_t, shared_ptr<DuckClientRenderer>>& playersData;
    Image bg;

    vector<shared_ptr<DuckColorItemGUI>> ducksGUI;

public:
    ShowColorsScreen(Camera& cam, map<PlayerID_t, shared_ptr<DuckClientRenderer>>& ducks):
            cam(cam),
            playersData(ducks),
            bg(RectTransform(Vector2D::Zero(), Vector2D(2000, 2000)),
               ColorExtension::Black().SetAlpha(180)) {

        Vector2D initialPos(-100, 100);
        for (const auto& it: ducks) {
            ducksGUI.emplace_back(std::make_shared<DuckColorItemGUI>(initialPos, *it.second));
            initialPos += Vector2D::Down() * 80;
        }
    }

    void Run(Callback drawBack) {

        bool running = true;

        ImageTween bgTween(bg, ColorExtension::Empty(), 0.7f, [&running]() { running = false; });

        Timer timer(3.0f, [&bgTween]() { bgTween.Play(); });

        timer.Start();

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

            drawBack();

            timer.Update(cam.GetRateDeltatime());
            TweenManager::GetInstance().Update(cam.GetRateDeltatime());
            GUIManager::GetInstance().Draw(cam);

            cam.Render();
            SDL_Delay(cam.GetRateMiliseconds());
        }
    }

    ~ShowColorsScreen() = default;
};

#endif
