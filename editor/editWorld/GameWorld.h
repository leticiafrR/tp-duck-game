#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <list>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "client/gameplay/CameraController.h"
#include "client/gameplay/GameplayGUI.h"
#include "client/rendering/BulletRenderer.h"
#include "client/rendering/CollectableRenderer.h"
#include "client/rendering/DuckClientRenderer.h"
#include "client/screens/ShowColorsScreen.h"
#include "client/tweening/ImageTween.h"
#include "client/tweening/TweenManager.h"
#include "common/playerIdentifier.h"
#include "multimedia/2d/MapBlock2D.h"
#include "multimedia/2d/Object2D.h"
#include "multimedia/Definitions.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Image.h"

#include "mapEditor.h"

using std::list;
using std::set;
using std::shared_ptr;
using std::unordered_map;
using std::vector;

class GameWorld {
private:
    Camera& cam;
    CameraController camController;
    Object2D mapBg;

    map<PlayerID_t, std::shared_ptr<DuckClientRenderer>> players;
    vector<MapBlock2D> mapBlocks;
    unordered_map<CollectableID_t, CollectableRenderer> collectables;

    GameplayGUI gui;

    set<int> pressedKeysSet;

    bool running = false;
    bool finishing = true;

    void InitPlayers(const MatchStartDto& matchData, const Snapshot& firstSnapshot);

    void InitMap(GameSceneDto mapData);

    void DespawnCollectable(CollectableID_t id);
    void SpawnCollectable(CollectableSpawnEventDto collectableData);

    void TakeInput();

    void TakeSnapshots(Callback OnLastSnapshot);

    void UpdateGame(const Snapshot& snapshot);

    void DrawGameWorld();

    void InitGUI();

public:
    GameWorld(Camera& c, MatchStartDto matchData, GameSceneDto mapData, Snapshot firstSnapshot);
    ~GameWorld();

    void Run(bool isInitial);
};

#endif
