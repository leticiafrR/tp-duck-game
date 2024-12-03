#ifndef GAME_STATUS_SCREEN_H
#define GAME_STATUS_SCREEN_H

#include <algorithm>
#include <list>
#include <optional>
#include <unordered_map>
#include <vector>

#include "client/rendering/DuckClientRenderer.h"
#include "client/utils/Timer.h"
#include "data/dataTransferObjects.h"
#include "multimedia/BaseScreen.h"
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
public:
    DuckResultItemGUI(Vector2D pos, GUIManager& guiManager, const PlayerData& duck,
                      DuckData duckData, int count);

    ~DuckResultItemGUI();
};

class GameStatusScreen: public BaseScreen {
private:
    Button* btnBack;
    Timer timer;

    list<DuckResultItemGUI> ducksGUI;

    void InitPlayersDisplay(vector<PlayerData> players, unordered_map<PlayerID_t, int> gameResults,
                            DuckData duckData);

public:
    GameStatusScreen(Camera& cam, ResourceManager& resource, bool& wasClosed,
                     vector<PlayerData> players, unordered_map<PlayerID_t, int> gameResults,
                     DuckData duckData, std::optional<PlayerData> winner);

    void InitRun() override;
    void TakeInput(SDL_Event event) override;
    void Update(float deltaTime) override;

    ~GameStatusScreen();
};

#endif
