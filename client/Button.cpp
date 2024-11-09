#include "Button.h"

#include "ButtonsManager.h"
#include "ColorExtension.h"

Button::Button(RectTransform rect, Callback onClick, Color color):
        rect(rect),
        onClick(onClick),
        color(color),
        targetColor(color),
        pressedColor(ColorExtension::AddValue(color, -50)) {
    ButtonsManager::GetInstance().AddButton(this);
}
Button::~Button() { ButtonsManager::GetInstance().RemoveButton(this); }

bool Button::IsMouseOver(float mouseX, float mouseY, Camera& cam) {
    Rect sdlRect = cam.RectTransformToRenderRect(rect);
    return mouseX > sdlRect.x && mouseX < sdlRect.x + sdlRect.w && mouseY > sdlRect.y &&
           mouseY < sdlRect.y + sdlRect.h;
}

void Button::Draw(Camera& cam) { cam.DrawGUI(rect, targetColor); }

void Button::HandleEvent(const SDL_Event& e, int mouseX, int mouseY, Camera& cam) {
    bool isMouseOver = IsMouseOver(mouseX, mouseY, cam);

    if (e.type == SDL_MOUSEMOTION && !isPressed) {
        targetColor = isMouseOver ? ColorExtension::AddValue(color, -12) : color;
    }

    if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (isMouseOver) {
            targetColor = pressedColor;
            isPressed = true;
        }

    } else if (e.type == SDL_MOUSEBUTTONUP) {
        if (isMouseOver && isPressed) {
            onClick();
        }
        targetColor = color;
        isPressed = false;
    }
}
