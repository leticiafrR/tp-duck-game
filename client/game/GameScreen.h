#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <memory>
#include <unordered_map>
#include <vector>

#include "client/Framework.h"
#include "client/FrameworkUI.h"
#include "client/network/Client.h"
#include "common/playerIdentifier.h"
#include "controllers/Controllers.h"

#include "CameraController.h"
#include "ClientControls.h"
#include "GameGUI.h"
#include "ShowColorsPanel.h"

using std::list;
using std::shared_ptr;
using std::unordered_map;
using std::vector;

class Gameplay: public BaseScreen {
private:
    Client& client;
    bool isInitial;
    CameraController camController;
    Object2D mapBg;

    ImageTween fadePanelTween;

    vector<MapBlock2D> mapBlocks;

    ClientControls controls;

    ThrowablesController throwablesController;
    CollectablesController collectablesController;
    BulletsController bulletsController;
    BoxesController boxesController;
    PlayersController ducksController;
    GameplayGUI gui;
    ShowColorsScreen showColorsPanel;

    bool finishing = true;

    void InitPlayers(const MatchStartDto& matchData, const Snapshot& firstSnapshot);

    void InitMap(GameSceneDto mapData);

    void TakeSnapshots(Callback OnLastSnapshot);

    void UpdateGame(const Snapshot& snapshot);

    void DrawGameWorld(float deltaTime);

    void InitGUI();

    void InitRun() override;
    void TakeInput(SDL_Event event) override;
    void Update(float deltaTime) override;

public:
    Gameplay(Client& cl, Camera& cam, ResourceManager& resource, bool& wasClosed,
             MatchStartDto matchData, GameSceneDto mapData, Snapshot firstSnapshot, bool isInitial);
    ~Gameplay();
};

#endif
