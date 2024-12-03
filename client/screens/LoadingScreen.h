#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H

#include <string>

#include "multimedia/BaseScreen.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/Definitions.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Image.h"
#include "multimedia/gui/Text.h"

class LoadingScreen: public BaseScreen {
private:
    Function<bool> endFunction;

public:
    LoadingScreen(Camera& cam, ResourceManager& resource, bool& wasClosed,
                  Function<bool> endFunction, const string& text = "", bool lockerOnly = false);

    ~LoadingScreen();

    void InitRun() override;
    void TakeInput(SDL_Event event) override;
    void Update(float deltaTime) override;
};

#endif
