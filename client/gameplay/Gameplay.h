#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <list>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "client/gameplay/CameraController.h"
#include "client/gameplay/GameplayGUI.h"
#include "client/network/Client.h"
#include "client/rendering/BulletRenderer.h"
#include "client/rendering/CollectableRenderer.h"
#include "client/rendering/DuckClientRenderer.h"
#include "client/screens/ShowColorsScreen.h"
#include "client/tweening/ImageTween.h"
#include "client/tweening/TweenManager.h"
#include "common/playerIdentifier.h"
#include "multimedia/Definitions.h"
#include "multimedia/GUIManager.h"
#include "multimedia/Image.h"
#include "multimedia/MapBlock2D.h"
#include "multimedia/Object2D.h"

using std::list;
using std::set;
using std::shared_ptr;
using std::unordered_map;
using std::vector;

class Gameplay {
private:
    Client& client;
    Camera& cam;
    CameraController camController;
    Object2D mapBg;

    vector<PlayerData> playersData;
    map<PlayerID_t, std::shared_ptr<DuckClientRenderer>> players;
    vector<MapBlock2D> mapBlocks;
    list<BulletRenderer> bullets;
    unordered_map<CollectableID_t, CollectableRenderer> collectables;

    GameplayGUI gui;

    set<int> pressedKeysSet;

    bool running = false;
    bool finishing = true;

    void InitPlayers(const MatchStartDto& matchData, const Snapshot& firstSnapshot);

    void InitMap(GameSceneDto mapData);

    void BulletsReapDead();

    void DespawnCollectable(CollectableID_t id);
    void SpawnCollectable(CollectableSpawnEventDto collectableData);

    void TakeInput();

    void TakeSnapshots(Callback OnLastSnapshot);

    void UpdateGame(const Snapshot& snapshot);

    void DrawGameWorld();

    void InitGUI();

public:
    Gameplay(Client& cl, Camera& c, MatchStartDto matchData, GameSceneDto mapData,
             Snapshot firstSnapshot);
    ~Gameplay();

    void Run(bool isInitial);
};

#endif
