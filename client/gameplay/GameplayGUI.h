#ifndef GAMEPLAY_GUI_H
#define GAMEPLAY_GUI_H

#include <memory>
#include <string>
#include <unordered_map>

#include "client/rendering/SpriteRendererData.h"
#include "data/snapshot.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Image.h"
#include "multimedia/gui/Text.h"
#include "multimedia/resource/ResourceData.h"

using std::make_shared;
using std::shared_ptr;
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
