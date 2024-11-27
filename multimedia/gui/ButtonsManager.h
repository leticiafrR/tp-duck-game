#ifndef BUTTONS_MANAGER_H
#define BUTTONS_MANAGER_H

#include <vector>

#include "multimedia/Camera.h"

#include "Button.h"

class ButtonsManager {
private:
    std::vector<Button*> buttons;

    ButtonsManager();
    ~ButtonsManager();

public:
    static ButtonsManager& GetInstance();

    void AddButton(Button* btn);

    void RemoveButton(Button* btn);

    void HandleEvent(const SDL_Event& e, Camera& cam);

    // Remove copy
    ButtonsManager(const ButtonsManager&) = delete;
    ButtonsManager& operator=(const ButtonsManager&) = delete;
};

#endif
