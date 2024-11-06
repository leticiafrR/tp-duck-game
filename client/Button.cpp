#include "Button.h"

#include "ButtonsManager.h"
#include "ColorExtension.h"

Button::Button(Rect rect, Callback onClick, Color color):
        rect(rect),
        onClick(onClick),
        color(color),
        targetColor(color),
        pressedColor(ColorExtension::AddValue(color, -50)) {
    ButtonsManager::GetInstance().AddButton(this);
}
Button::~Button() { ButtonsManager::GetInstance().RemoveButton(this); }

bool Button::IsMouseOver(float mouseX, float mouseY) {
    return mouseX > rect.x && mouseX < rect.x + rect.w && mouseY > rect.y &&
           mouseY < rect.y + rect.h;
}

void Button::Draw(Camera& cam) { cam.DrawGUI(rect, targetColor); }

void Button::HandleEvent(const SDL_Event& e, int mouseX, int mouseY) {
    bool isMouseOver = IsMouseOver(mouseX, mouseY);

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
