#ifndef CONTROLS_SCREEN_H
#define CONTROLS_SCREEN_H

#include <list>
#include <memory>
#include <string>

#include "client/utils/GameKit.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/Image.h"
#include "multimedia/gui/Text.h"

using std::list;
using std::make_shared;
using std::shared_ptr;
using std::string;

class KeyItemGUI {
private:
    Image imgBg;
    Text txtKey;

public:
    KeyItemGUI(const string& key, Vector2D pos, Vector2D size = Vector2D(60, 60),
               float textAngle = 0);

    void SetActive(bool visible);

    ~KeyItemGUI();
};


class ControlsScreen {
private:
    Image imgBg;
    Button btnBack;

    list<Text> texts;

    list<KeyItemGUI> playerKeys;

    void InitTexts();

    void InitPlayer1Keys();

    void InitPlayer2Keys();

public:
    explicit ControlsScreen(GameKit& gameKit);

    void SetActive(bool active);

    ~ControlsScreen();
};

#endif
