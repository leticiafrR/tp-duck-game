#ifndef GAME_STATUS_SCREEN_H
#define GAME_STATUS_SCREEN_H

#include <algorithm>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

#include "client/rendering/DuckClientRenderer.h"
#include "client/utils/Timer.h"
#include "data/dataTransferObjects.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/ButtonsManager.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Text.h"

#include "ShowColorsScreen.h"

using std::make_shared;
using std::shared_ptr;
using std::unordered_map;
using std::vector;

class DuckResultItemGUI {
private:
    Image imgColor;
    Text txtNickname;
    Text txtCount;

public:
    DuckResultItemGUI(Vector2D pos, const PlayerData& duck, int count);

    ~DuckResultItemGUI();
};

class GameStatusScreen {
private:
    Camera& cam;
    Image imgBg;
    Text txtTitle;
    Button btnBack;

    vector<shared_ptr<DuckResultItemGUI>> ducksGUI;

    bool running = true;

public:
    GameStatusScreen(Camera& cam, vector<PlayerData> players,
                     unordered_map<PlayerID_t, int> gameResults, std::optional<PlayerData> winner);

    void Run();

    ~GameStatusScreen();
};

#endif
