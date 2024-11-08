#ifndef BUTTONS_MANAGER_H
#define BUTTONS_MANAGER_H

#include <vector>

#include "Button.h"
#include "Camera.h"

class ButtonsManager {
private:
    ButtonsManager() = default;
    std::vector<Button*> buttons;

public:
    static ButtonsManager& GetInstance() {
        static ButtonsManager Instance;
        return Instance;
    }

    void AddButton(Button* btn) { buttons.push_back(btn); }

    void RemoveButton(Button* btn) {
        auto it = std::find(buttons.begin(), buttons.end(), btn);
        if (it != buttons.end()) {
            buttons.erase(it);
        }
    }

    void HandleEvent(const SDL_Event& e) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        for (auto btn: buttons) {
            btn->HandleEvent(e, mouseX, mouseY);
        }
    }

    void Draw(Camera& cam) {
        for (auto btn: buttons) {
            btn->Draw(cam);
        }
    }

    // Remove copy
    ButtonsManager(const ButtonsManager&) = delete;
    ButtonsManager& operator=(const ButtonsManager&) = delete;

    ~ButtonsManager() = default;
};

#endif
