#ifndef GAME_STATUS_SCREEN_H
#define GAME_STATUS_SCREEN_H

#include <algorithm>
#include <list>
#include <optional>
#include <unordered_map>
#include <vector>

#include "client/BaseScreen.h"
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

using std::list;
using std::unordered_map;
using std::vector;

class DuckResultItemGUI {
private:
    Image imgColor;
    Text txtNickname;
    Text txtCount;

public:
    DuckResultItemGUI(Vector2D pos, const PlayerData& duck, DuckData duckData, int count);

    ~DuckResultItemGUI();
};

class GameStatusScreen: public BaseScreen {
private:
    Image imgBg;
    Text txtTitle;
    Button btnBack;
    Timer timer;

    list<DuckResultItemGUI> ducksGUI;

    void InitPlayersDisplay(vector<PlayerData> players, unordered_map<PlayerID_t, int> gameResults,
                            DuckData duckData);

public:
    GameStatusScreen(GameKit& kit, bool& wasClosed, vector<PlayerData> players,
                     unordered_map<PlayerID_t, int> gameResults, DuckData duckData,
                     std::optional<PlayerData> winner);

    void InitRun() override;
    void TakeInput(SDL_Event event) override;
    void Update(float deltaTime) override;

    ~GameStatusScreen();
};

#endif
