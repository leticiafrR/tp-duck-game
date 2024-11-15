#include "Button.h"

#include "ButtonsManager.h"
#include "ColorExtension.h"

Button::Button(RectTransform rect, Callback onClick, Color color, int layer):
        image(rect, color, layer),
        onClick(onClick),
        color(color),
        pressedColor(ColorExtension::AddValue(color, -50)) {
    ButtonsManager::GetInstance().AddButton(this);
}
Button::~Button() { ButtonsManager::GetInstance().RemoveButton(this); }

bool Button::IsMouseOver(float mouseX, float mouseY, Camera& cam) {
    Rect sdlRect = cam.RectTransformToRenderRect(image.GetRectTransform());
    return mouseX > sdlRect.x && mouseX < sdlRect.x + sdlRect.w && mouseY > sdlRect.y &&
           mouseY < sdlRect.y + sdlRect.h;
}

void Button::Draw(Camera& cam) { image.Draw(cam); }

void Button::HandleEvent(const SDL_Event& e, int mouseX, int mouseY, Camera& cam) {
    bool isMouseOver = IsMouseOver(mouseX, mouseY, cam);

    if (e.type == SDL_MOUSEMOTION && !isPressed) {
        image.SetColor(isMouseOver ? ColorExtension::AddValue(color, -12) : color);
    }

    if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (isMouseOver) {
            image.SetColor(pressedColor);
            isPressed = true;
        }

    } else if (e.type == SDL_MOUSEBUTTONUP) {
        if (isMouseOver && isPressed) {
            onClick();
        }
        image.SetColor(color);
        isPressed = false;
    }
}
