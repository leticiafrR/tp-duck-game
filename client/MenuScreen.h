#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <string>

#include "tweening/TransformTween.h"
#include "tweening/TweenManager.h"

#include "Button.h"
#include "ButtonsManager.h"
#include "Camera.h"
#include "ColorExtension.h"
#include "GUIManager.h"
#include "Rate.h"
#include "SDLExtension.h"
#include "Text.h"

using std::string;

class MenuScreen {
private:
    const int MAX_NAME_SIZE = 12;

    Camera& cam;
    Rate rate;

    Image bgImage;
    Image logoImage;

    Image inputBgImage;

    Text nicknamePlaceHolderText;

    Text nicknameText;

    Button startButton;
    Text buttonText;

    bool running = true;
    string nicknameInput = "";

    void TakeInput() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit(0);
                    break;
                case SDL_KEYDOWN: {
                    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;

                    switch (keyEvent.keysym.sym) {
                        case SDLK_BACKSPACE:
                            if (nicknameInput.size() > 0)
                                nicknameInput.pop_back();
                            break;
                        default:
                            if ((int)nicknameInput.size() == MAX_NAME_SIZE)
                                break;
                            if (!SDLExtension::IsAlphaNumeric(keyEvent.keysym.sym))
                                break;

                            const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

                            bool shiftPressed = (currentKeyStates[SDL_SCANCODE_LSHIFT] ||
                                                 currentKeyStates[SDL_SCANCODE_RSHIFT]);

                            char c = static_cast<char>(keyEvent.keysym.sym);
                            if (shiftPressed)
                                c = std::toupper(c);
                            nicknameInput.push_back(c);
                            break;
                    }
                    break;
                }
            }

            ButtonsManager::GetInstance().HandleEvent(event, cam);
        }
    }

public:
    MenuScreen(Camera& c, const Rate& r):
            cam(c),
            rate(r),
            bgImage("duck_game_bg.jpg", RectTransform(Vector2D::Zero(), Vector2D(2133, 1200))),
            logoImage("duck_game_logo.png", RectTransform(Vector2D(0, 240), Vector2D(575, 300))),
            inputBgImage(RectTransform(Transform(Vector2D(0, -2), Vector2D(750, 80))),
                         ColorExtension::Black().SetAlpha(80)),
            nicknamePlaceHolderText("Write your nickname", 50,
                                    RectTransform(Transform(Vector2D(0, 0), Vector2D(750, 80)),
                                                  Vector2D(0.5, 0.5), Vector2D(0.5, 0.5)),
                                    ColorExtension::White().SetAlpha(120)),
            nicknameText("", 50,
                         RectTransform(Transform(Vector2D(0, 0), Vector2D(750, 80)),
                                       Vector2D(0.5, 0.5), Vector2D(0.5, 0.5)),
                         ColorExtension::White()),
            startButton(
                    "button_1.png",
                    RectTransform(Transform(Vector2D(0, -200), Vector2D(200, 80)),
                                  Vector2D(0.5, 0.5), Vector2D(0.5, 0.5)),
                    [this]() {
                        running = false;
                        AudioManager::GetInstance().PlayButtonSFX();
                    },
                    Color(40, 40, 40)),

            buttonText("START", 200,
                       RectTransform(Transform(Vector2D(0, -200), Vector2D(150, 80)),
                                     Vector2D(0.5, 0.5), Vector2D(0.5, 0.5)),
                       ColorExtension::White()) {}

    string Render() {
        running = true;

        Transform& btnTransform = startButton.GetRectTransform().GetTransform();
        Transform& textTransform = buttonText.GetRectTransform().GetTransform();

        TransformTween btnTween(btnTransform, btnTransform.GetSize() * 1.1f, 0.6f);
        TransformTween textTween(textTransform, textTransform.GetSize() * 1.1f, 0.6f);
        btnTween.SetLoops(-1, LoopType::Yoyo);
        textTween.SetLoops(-1, LoopType::Yoyo);
        btnTween.Play();
        textTween.Play();

        while (running) {
            cam.Clean();

            TakeInput();

            nicknameText.SetText(nicknameInput);

            nicknamePlaceHolderText.SetVisible(nicknameInput.size() == 0);
            startButton.SetVisible(nicknameInput.size() != 0);
            buttonText.SetVisible(nicknameInput.size() != 0);

            GUIManager::GetInstance().Draw(cam);
            TweenManager::GetInstance().Update(rate.GetDeltaTime());

            cam.Render();
            SDL_Delay(rate.GetMiliseconds());
        }

        return nicknameInput;
    }

    ~MenuScreen() {
        cam.ClearCacheItem("duck_game_bg.jpg");
        cam.ClearCacheItem("duck_game_logo.png");
    }
};

#endif
