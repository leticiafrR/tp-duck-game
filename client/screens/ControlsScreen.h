#ifndef CONTROLS_SCREEN_H
#define CONTROLS_SCREEN_H

#include <memory>
#include <string>
#include <vector>

#include "multimedia/AudioManager.h"
#include "multimedia/Button.h"
#include "multimedia/Image.h"
#include "multimedia/Text.h"

using std::make_shared;
using std::shared_ptr;
using std::string;
using std::vector;

class KeyItemGUI {
private:
    shared_ptr<Image> imgBg;
    shared_ptr<Text> txtKey;

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

    vector<shared_ptr<Text>> texts;

    vector<KeyItemGUI> playerKeys;

    void InitTexts();

    void InitPlayer1Keys();

    void InitPlayer2Keys();

public:
    ControlsScreen();

    void SetActive(bool active);

    ~ControlsScreen();
};

#endif
