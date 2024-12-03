#ifndef CONTROLS_PANEL_H
#define CONTROLS_PANEL_H

#include <list>
#include <memory>
#include <string>

#include "multimedia/BaseScreen.h"

using std::list;
using std::string;

class KeyItemGUI {
private:
    Image* imgBg;
    Text* txtKey;

public:
    KeyItemGUI(GUIManager& guiManager, const string& key, Vector2D pos,
               Vector2D size = Vector2D(60, 60), float textAngle = 0);

    void SetActive(bool visible);

    ~KeyItemGUI();
};


class ControlsScreen {
private:
    Image* imgBg;
    Button* btnBack;

    GUIManager& guiManager;

    list<Text*> texts;

    list<KeyItemGUI> playerKeys;

    void AddText(string text, int x, int y);
    void AddPlayerKey(string key, Vector2D pos, Vector2D size = Vector2D(60, 60),
                      float textAngle = 0);

    void InitTexts();

    void InitPlayer1Keys();

    void InitPlayer2Keys();

public:
    ControlsScreen(AudioManager& audioPlayer, GUIManager& guiManager);

    void SetActive(bool active);

    ~ControlsScreen();
};

#endif
