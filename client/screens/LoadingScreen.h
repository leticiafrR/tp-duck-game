#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H

#include <string>

#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/Definitions.h"
#include "multimedia/GUIManager.h"
#include "multimedia/Image.h"
#include "multimedia/Text.h"

class LoadingScreen {
private:
    Camera& cam;
    Function<bool> endFunction;

public:
    LoadingScreen(Camera& cam, Function<bool> endFunction);

    ~LoadingScreen();

    void Run(const string& text = "", bool lockerOnly = false);
};

#endif
