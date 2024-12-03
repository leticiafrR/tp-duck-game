#ifndef GAME_GUI_H
#define GAME_GUI_H

#include <memory>
#include <string>
#include <unordered_map>

#include "client/Framework.h"
#include "client/FrameworkUI.h"
#include "data/snapshot.h"

using std::string;
using std::unordered_map;

class LocalPlayerGUI {
private:
public:
    LocalPlayerGUI(GUIManager& guiManager, DuckData duckData, Color duckColor,
                   const string& nickname, bool isOne);
    ~LocalPlayerGUI();
};

class GameplayGUI {
private:
    GUIManager& guiManager;
    DuckData duckData;

    std::optional<LocalPlayerGUI> player1GUI;
    std::optional<LocalPlayerGUI> player2GUI;

public:
    GameplayGUI(GUIManager& guiManager, DuckData duckData);
    ~GameplayGUI();

    void InitPlayer1GUI(Color color, const string& nickname);

    void InitPlayer2GUI(Color color, const string& nickname);
};

#endif
