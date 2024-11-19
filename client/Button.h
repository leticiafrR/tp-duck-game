#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "Camera.h"
#include "Definitions.h"
#include "Image.h"
#include "RectTransform.h"

using namespace SDL2pp;  // NOLINT

class Button: public Image {
private:
    std::function<void()> onClick;
    Color normalColor;
    Color pressedColor;
    Color disabledColor;
    bool isPressed;
    bool interactable;

public:
    Button(RectTransform rect, Callback onClick, Color color = Color(255, 255, 255),
           int layerOrder = 0);
    ~Button();

    static bool IsMouseOver(RectTransform rect, float mouseX, float mouseY, Camera& cam);

    bool IsTarget(int mouseX, int mouseY, Camera& cam);

    void HandleEvent(const SDL_Event& e, int mouseX, int mouseY, Camera& cam);

    void SetInteractable(bool interactable);

    void SetCallback(Callback onClick) { this->onClick = onClick; }
};

#endif
