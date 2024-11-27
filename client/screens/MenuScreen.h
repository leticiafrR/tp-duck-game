#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <string>

#include "client/tweening/TransformTween.h"
#include "client/tweening/TweenManager.h"
#include "multimedia/AudioManager.h"
#include "multimedia/Button.h"
#include "multimedia/ButtonsManager.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/GUIManager.h"
#include "multimedia/KeyboardExtension.h"
#include "multimedia/Text.h"

using std::string;

class MenuScreen {
private:
    const int MAX_NAME_SIZE = 12;

    Camera& cam;

    Image bgImage;
    Image logoImage;

    Image inputBgImage;

    Text nicknamePlaceHolderText;

    Text nicknameText;

    Button startButton;
    Text buttonText;

    bool running = true;
    string nicknameInput = "";

    void TakeInput();

public:
    explicit MenuScreen(Camera& c);

    ~MenuScreen();

    string Render();
};

#endif
