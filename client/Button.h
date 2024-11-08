#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "Camera.h"

using namespace SDL2pp;  // NOLINT
using Callback = std::function<void()>;

class Button {
private:
    Rect rect;
    std::function<void()> onClick;
    Color color;
    Color targetColor;
    Color pressedColor;
    bool isPressed;

public:
    Button(Rect rect, Callback onClick, Color color = Color(255, 255, 255));
    ~Button();

    bool IsMouseOver(float mouseX, float mouseY);

    // bool IsPressed() { return isPressed; }

    // void PressDown() { isPressed = true; }

    void Draw(Camera& cam);

    // void PressUp(bool executeCallback) {
    //     isPressed = false;
    //     if (executeCallback)
    //         onClick();
    // }

    void HandleEvent(const SDL_Event& e, int mouseX, int mouseY);
};

#endif
