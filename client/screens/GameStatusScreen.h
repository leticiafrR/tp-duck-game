#ifndef GAME_STATUS_SCREEN_H
#define GAME_STATUS_SCREEN_H

#include <algorithm>
#include <memory>
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

class GameStatusScreen: public BaseScreen {
private:
    Image imgBg;
    Text txtTitle;
    Button btnBack;
    Timer timer;

    vector<shared_ptr<DuckResultItemGUI>> ducksGUI;

public:
    GameStatusScreen(Camera& cam, bool& wasClosed, vector<PlayerData> players,
                     unordered_map<PlayerID_t, int> gameResults, std::optional<PlayerData> winner);

    void InitPlayersDisplay(vector<PlayerData> players, unordered_map<PlayerID_t, int> gameResults);

    void InitRun() override;
    void TakeInput(SDL_Event event) override;
    void Update(float deltaTime) override;

    ~GameStatusScreen();
};

#endif
