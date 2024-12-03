#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "multimedia/Camera.h"
#include "multimedia/Definitions.h"

#include "Image.h"
#include "RectTransform.h"

using namespace SDL2pp;  // NOLINT

class Button: public Image {
private:
    std::function<void()> onClick;
    Color normalColor;
    Color pressedColor;
    Color disabledColor;
    bool interactable;
    bool isPressed;

public:
    Button(RectTransform rect = RectTransform(), Color color = Color(255, 255, 255),
           int layerOrder = 0);

    explicit Button(
            RectTransform rect, Callback onClick = []() {}, Color color = Color(255, 255, 255),
            int layerOrder = 0);
    Button(const std::string& filename, RectTransform rect, Callback onClick,
           Color color = Color(255, 255, 255), int layerOrder = 0);
    ~Button();

    static bool IsMouseOver(RectTransform rect, float mouseX, float mouseY, Camera& cam);

    bool IsTarget(int mouseX, int mouseY, Camera& cam, vector<GraphicUI*> graphics);

    void HandleEvent(const SDL_Event& e, int mouseX, int mouseY, Camera& cam,
                     vector<GraphicUI*> graphics);

    void SetInteractable(bool interactable);

    void SetCallback(Callback onClick) { this->onClick = onClick; }
};

#endif
