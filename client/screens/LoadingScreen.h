#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H

#include <string>

#include "client/BaseScreen.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/Definitions.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Image.h"
#include "multimedia/gui/Text.h"

class LoadingScreen: BaseScreen {
private:
    Function<bool> endFunction;

public:
    LoadingScreen(Camera& cam, bool& wasClosed, Function<bool> endFunction);

    ~LoadingScreen();

    void Run(const string& text = "", bool lockerOnly = false);

    void InitRun() override;
    void TakeInput(SDL_Event event) override;
    void Update(float deltaTime) override;
};

#endif
