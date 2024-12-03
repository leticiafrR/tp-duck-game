#ifndef BUTTONS_MANAGER_H
#define BUTTONS_MANAGER_H

#include <vector>

#include "multimedia/Camera.h"

#include "Button.h"

class ButtonsManager {
private:
    std::vector<Button*> buttons;

public:
    ButtonsManager();
    ~ButtonsManager();

    void AddButton(Button* btn);

    void RemoveButton(Button* btn);

    void HandleEvent(const SDL_Event& e, Camera& cam, vector<GraphicUI*> graphics);

    // Remove copy
    ButtonsManager(const ButtonsManager&) = delete;
    ButtonsManager& operator=(const ButtonsManager&) = delete;
};

#endif
