#ifndef MATCH_LIST_SCREEN_H
#define MATCH_LIST_SCREEN_H

#include <string>

#include "Button.h"
#include "ButtonsManager.h"
#include "Camera.h"
#include "ColorExtension.h"
#include "Rate.h"
#include "SDLExtension.h"
#include "Text.h"

using std::string;

class MatchListScreen {
private:
    Camera& cam;
    Rate rate;

public:
    MatchListScreen(Camera& cam, const Rate& rate): cam(cam), rate(rate) {}

    void Render() {
        bool running = true;

        Text titleText("SELECT OR CREATE A MATCH", "pixel.ttf", 160,
                       RectTransform(Transform(Vector2D(3, 157), Vector2D(500, 160)),
                                     Vector2D(0.5, 0.5), Vector2D(0.5, 0.5)),
                       ColorExtension::White());

        Button createButton(
                RectTransform(Transform(Vector2D(0, -200), Vector2D(200, 80)), Vector2D(0.5, 0.5),
                              Vector2D(0.5, 0.5)),
                [&running]() { running = false; }, Color(40, 40, 40));
        Text createButtonText("CREATE", "pixel.ttf", 30,
                              RectTransform(Transform(Vector2D(0, -200), Vector2D(200, 80)),
                                            Vector2D(0.5, 0.5), Vector2D(0.5, 0.5)),
                              ColorExtension::White());

        Button matchButton(
                RectTransform(Transform(Vector2D(0, 0), Vector2D(900, 120))),
                [&running]() { running = false; }, Color(160, 160, 160));

        Text matchOwnerText("josValentin lobby", "pixel.ttf", 30,
                            RectTransform(Transform(Vector2D(-280, 0), Vector2D(300, 120))),
                            ColorExtension::White());

        Text matchPlayersText("Players 2/5", "pixel.ttf", 30,
                              RectTransform(Transform(Vector2D(0, 0), Vector2D(180, 120))),
                              ColorExtension::White());

        Button matchJoinButton(
                RectTransform(Transform(Vector2D(280, 0), Vector2D(150, 80))),
                [&running]() { running = false; }, Color(40, 40, 40));

        Text matchJoinText("Join", "pixel.ttf", 30,
                           RectTransform(Transform(Vector2D(280, 0), Vector2D(150, 80))),
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

                ButtonsManager::GetInstance().HandleEvent(event, cam);
            }

            ButtonsManager::GetInstance().Draw(cam);

            titleText.Draw(cam);
            createButtonText.Draw(cam);

            matchOwnerText.Draw(cam);
            matchPlayersText.Draw(cam);
            matchJoinText.Draw(cam);

            cam.Render();
            SDL_Delay(rate.GetMiliseconds());
        }
    }

    ~MatchListScreen() = default;
};

#endif
