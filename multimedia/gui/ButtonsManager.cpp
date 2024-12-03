#include "ButtonsManager.h"

ButtonsManager::ButtonsManager() = default;
ButtonsManager::~ButtonsManager() = default;

void ButtonsManager::AddButton(Button* btn) { buttons.push_back(btn); }

void ButtonsManager::RemoveButton(Button* btn) {
    auto it = std::find(buttons.begin(), buttons.end(), btn);
    if (it != buttons.end()) {
        buttons.erase(it);
    }
}

void ButtonsManager::HandleEvent(const SDL_Event& e, Camera& cam, vector<GraphicUI*> graphics) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    for (auto btn: buttons) {
        btn->HandleEvent(e, mouseX, mouseY, cam, graphics);
    }
}
