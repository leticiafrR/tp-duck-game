#include "Button.h"

#include <vector>

#include "multimedia/ColorExtension.h"

#include "ButtonsManager.h"
#include "GUIManager.h"

using std::vector;

Button::Button(RectTransform rect, Color color, int layerOrder):
        Image(rect, color, layerOrder),
        onClick([]() {}),
        normalColor(color),
        pressedColor(ColorExtension::AddValue(color, -50)),
        disabledColor(color.SetAlpha(120)),
        interactable(true),
        isPressed(false) {}

Button::Button(RectTransform rect, Callback onClick, Color color, int layerOrder):
        Image(rect, color, layerOrder),
        onClick(onClick),
        normalColor(color),
        pressedColor(ColorExtension::AddValue(color, -50)),
        disabledColor(color.SetAlpha(120)),
        interactable(true),
        isPressed(false) {}

Button::Button(const std::string& filename, RectTransform rect, Callback onClick, Color color,
               int layerOrder):
        Image(filename, rect, color, layerOrder),
        onClick(onClick),
        normalColor(color),
        pressedColor(ColorExtension::AddValue(color, -50)),
        disabledColor(color.SetAlpha(120)),
        interactable(true),
        isPressed(false) {}

Button::~Button() {}

bool Button::IsMouseOver(RectTransform rect, float mouseX, float mouseY, Camera& cam) {
    Rect sdlRect = cam.RectTransformToRenderRect(rect);
    return mouseX > sdlRect.x && mouseX < sdlRect.x + sdlRect.w && mouseY > sdlRect.y &&
           mouseY < sdlRect.y + sdlRect.h;
}

bool Button::IsTarget(int mouseX, int mouseY, Camera& cam, vector<GraphicUI*> graphics) {
    // Search for the first same layer in th sorted vector
    auto it = std::lower_bound(
            graphics.begin(), graphics.end(), this,
            [](GraphicUI* a, GraphicUI* b) { return a->GetLayerOrder() < b->GetLayerOrder(); });

    if (it != graphics.end() && (*it)->GetLayerOrder() >= this->GetLayerOrder()) {
        bool startCheckingFront = false;
        for (auto iter = it;
             iter != graphics.end() && (*iter)->GetLayerOrder() >= this->GetLayerOrder(); ++iter) {

            if ((*iter) == this) {
                startCheckingFront = true;
                continue;
            }
            if (!startCheckingFront)
                continue;
            if (!(*iter)->GetCanTarget()) {
                continue;
            }
            // If there is another target graphic in front, our button is not the target
            if (IsMouseOver((*iter)->GetRectTransform(), mouseX, mouseY, cam)) {
                return false;
            }
        }
    }
    return true;
}

void Button::SetInteractable(bool interactable) {
    SetColor(interactable ? normalColor : disabledColor);
    this->interactable = interactable;
}

void Button::HandleEvent(const SDL_Event& e, int mouseX, int mouseY, Camera& cam,
                         vector<GraphicUI*> graphics) {
    if (!interactable || !GetVisible())
        return;

    bool isMouseOver = IsMouseOver(GetRectTransform(), mouseX, mouseY, cam);

    if (isMouseOver)
        isMouseOver = IsTarget(mouseX, mouseY, cam, graphics);

    if (e.type == SDL_MOUSEMOTION && !isPressed) {
        SetColor(isMouseOver ? ColorExtension::AddValue(normalColor, -12) : normalColor);
    }

    if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (isMouseOver) {
            SetColor(pressedColor);
            isPressed = true;
        }

    } else if (e.type == SDL_MOUSEBUTTONUP) {
        SetColor(normalColor);
        if (isMouseOver && isPressed) {
            onClick();
        }
        isPressed = false;
    }
}
