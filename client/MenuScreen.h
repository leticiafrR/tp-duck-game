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
    Camera& cam;
    Rate rate;

    Text titleShadow;
    Text titleText;
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
            titleShadow("DUCK GAME", 160,
                        RectTransform(Transform(Vector2D(3, 157), Vector2D(500, 160)),
                                      Vector2D(0.5, 0.5), Vector2D(0.5, 0.5)),
                        ColorExtension::Black()),
            titleText("DUCK GAME", 160,
                      RectTransform(Transform(Vector2D(0, 160), Vector2D(500, 160)),
                                    Vector2D(0.5, 0.5), Vector2D(0.5, 0.5)),
                      ColorExtension::White()),
            nicknamePlaceHolderText("Write your nickname", 50,
                                    RectTransform(Transform(Vector2D(0, 0), Vector2D(800, 80)),
                                                  Vector2D(0.5, 0.5), Vector2D(0.5, 0.5)),
                                    ColorExtension::White().SetAlpha(120)),
            nicknameText("", 50,
                         RectTransform(Transform(Vector2D(0, 0), Vector2D(800, 80)),
                                       Vector2D(0.5, 0.5), Vector2D(0.5, 0.5)),
                         ColorExtension::White()),
            startButton(
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

    ~MenuScreen() = default;
};

#endif
