#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H

#include <string>

#include "Camera.h"
#include "ColorExtension.h"
#include "Rate.h"
#include "Text.h"

using BoolFunction = std::function<bool()>;

class LoadingScreen {
private:
    Camera& cam;
    Rate rate;
    BoolFunction endFunction;

public:
    LoadingScreen(Camera& cam, const Rate& rate, BoolFunction endFunction):
            cam(cam), rate(rate), endFunction(endFunction) {}

    void Render(const string& text) {
        Text titleText(text, 160,
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
            }

            if (endFunction()) {
                break;
            }

            titleText.Draw(cam);
            cam.Render();
            SDL_Delay(rate.GetMiliseconds());
        }
    }

    ~LoadingScreen() = default;
};

#endif
