#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "Camera.h"
#include "Image.h"
#include "RectTransform.h"

using namespace SDL2pp;  // NOLINT
using Callback = std::function<void()>;

class Button {
private:
    Image image;
    std::function<void()> onClick;
    Color color;
    Color pressedColor;
    bool isPressed;

public:
    Button(RectTransform rect, Callback onClick, Color color = Color(255, 255, 255), int layer = 0);
    ~Button();

    bool IsMouseOver(float mouseX, float mouseY, Camera& cam);

    void Draw(Camera& cam);

    RectTransform& GetRectTransform() { return image.GetRectTransform(); }

    void HandleEvent(const SDL_Event& e, int mouseX, int mouseY, Camera& cam);
};

#endif
