#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <list>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "client/BaseScreen.h"
#include "client/gameplay/CameraController.h"
#include "client/gameplay/GameplayGUI.h"
#include "client/network/Client.h"
#include "client/rendering/BulletRenderer.h"
#include "client/rendering/BulletsController.h"
#include "client/rendering/CollectableRenderer.h"
#include "client/rendering/CollectablesController.h"
#include "client/rendering/DuckClientRenderer.h"
#include "client/rendering/DucksController.h"
#include "client/rendering/ThrowableRenderer.h"
#include "client/rendering/ThrowablesController.h"
#include "client/screens/ShowColorsScreen.h"
#include "client/tweening/ImageTween.h"
#include "client/tweening/TweenManager.h"
#include "common/playerIdentifier.h"
#include "multimedia/2d/MapBlock2D.h"
#include "multimedia/2d/Object2D.h"
#include "multimedia/Definitions.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Image.h"

#include "ClientControls.h"

using std::list;
using std::set;
using std::shared_ptr;
using std::unordered_map;
using std::vector;

class Gameplay: public BaseScreen {
private:
    Client& client;
    bool isInitial;
    CameraController camController;
    Object2D mapBg;

    Image fadePanel;
    ImageTween fadePanelTween;

    vector<MapBlock2D> mapBlocks;
    ShowColorsScreen showColorsPanel;

    GameplayGUI gui;

    ClientControls controls;

    ResourceManager& resourceManager;
    AudioManager& audioManager;

    ThrowablesController throwablesController;
    CollectablesController collectablesController;
    BulletsController bulletsController;
    DucksController ducksController;

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
    Gameplay(Client& cl, GameKit& gameKit, bool& wasClosed, MatchStartDto matchData,
             GameSceneDto mapData, Snapshot firstSnapshot, bool isInitial);
    ~Gameplay();
};

#endif
