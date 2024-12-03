#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <string>

#include "client/Framework.h"
#include "client/FrameworkUI.h"

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
