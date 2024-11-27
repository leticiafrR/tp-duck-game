#ifndef SETLEVELNAME_H
#define SETLEVELNAME_H

#include <string>

#include "client/tweening/TransformTween.h"
#include "client/tweening/TweenManager.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/ButtonsManager.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Text.h"

using std::string;

class SetLevelName {
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
    explicit SetLevelName(Camera& c);

    string Render();

    ~SetLevelName();
};

#endif
