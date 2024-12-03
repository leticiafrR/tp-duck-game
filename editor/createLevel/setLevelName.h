#ifndef SETLEVELNAME_H
#define SETLEVELNAME_H

#include <string>

#include "client/tweening/TransformTween.h"
#include "client/tweening/TweenManager.h"
#include "multimedia/BaseScreen.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/ButtonsManager.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Text.h"

using std::string;

class SetLevelName: public BaseScreen {
private:
    const int MAX_NAME_SIZE = 12;

    Text* nicknamePlaceHolderText;
    Text* nicknameText;

    Button* startButton;
    Text* buttonText;

    string nicknameInput = "";

    void InitRun() override;
    void TakeInput(SDL_Event event) override;
    void Update(float deltaTime) override;

public:
    explicit SetLevelName(Camera& c, ResourceManager& resource, bool& wasclosed);

    string Render();

    ~SetLevelName();
};

#endif
