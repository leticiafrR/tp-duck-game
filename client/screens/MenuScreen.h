#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <string>

#include "client/tweening/TransformTween.h"
#include "client/tweening/TweenManager.h"
#include "multimedia/BaseScreen.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/KeyboardExtension.h"
#include "multimedia/audio/AudioManager.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/ButtonsManager.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Text.h"

using std::string;

class MenuScreen: public BaseScreen {
private:
    const int MAX_NAME_SIZE = 12;
    MenuData menuData;

    Text* nicknamePlaceHolderText;
    Text* nicknameText;

    Button* btnStart;
    Text* txtStartButton;

    string& nicknameInput;

    TransformTween btnStartTween;
    TransformTween txtStartButtonTween;

    void InitBackground();
    void InitInput();
    void InitStartButton();

    void InitRun() override;
    void TakeInput(SDL_Event event) override;
    void Update(float deltaTime) override;

public:
    explicit MenuScreen(Camera& cam, ResourceManager& resource, bool& wasClosed, string& input);

    ~MenuScreen();
};

#endif
