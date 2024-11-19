#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "Camera.h"
#include "Definitions.h"
#include "Image.h"
#include "RectTransform.h"

using namespace SDL2pp;  // NOLINT

class Button {
private:
    Image image;
    std::function<void()> onClick;
    Color color;
    Color pressedColor;
    Color disabledColor;
    bool isPressed;
    bool interactable;

public:
    Button(RectTransform rect, Callback onClick, Color color = Color(255, 255, 255),
           int layerOrder = 0);
    ~Button();

    static bool IsMouseOver(RectTransform rect, float mouseX, float mouseY, Camera& cam);

    void Draw(Camera& cam);

    RectTransform& GetRectTransform() { return image.GetRectTransform(); }

    bool IsTarget(int mouseX, int mouseY, Camera& cam);

    void HandleEvent(const SDL_Event& e, int mouseX, int mouseY, Camera& cam);

    void SetInteractable(bool interactable);

    void SetVisible(bool visible);

    int GetLayerOrder() { return image.GetLayerOrder(); }
};

#endif
