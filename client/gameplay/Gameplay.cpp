#include "Gameplay.h"

void Gameplay::InitPlayers(const MatchStartDto& matchData, const Snapshot& firstSnapshot) {
    ducksController.SpawnPlayers(matchData.duckSize, matchData.playersData, firstSnapshot.updates);
}

void Gameplay::InitMap(GameSceneDto mapData) {
    MapThemeData& themeData = resourceManager.GetMapThemeData(mapData.theme);

    for (size_t i = 0; i < mapData.groundBlocks.size(); i++) {
        auto groundData = mapData.groundBlocks[i];
        mapBlocks.emplace_back(themeData, groundData.mySpace);

        bool left =
                groundData.visibleEdges.find(VISIBLE_EDGES::LEFT) != groundData.visibleEdges.end();
        bool right =
                groundData.visibleEdges.find(VISIBLE_EDGES::RIGHT) != groundData.visibleEdges.end();
        bool top =
                groundData.visibleEdges.find(VISIBLE_EDGES::TOP) != groundData.visibleEdges.end();
        bool bottom = groundData.visibleEdges.find(VISIBLE_EDGES::BOTTOM) !=
                      groundData.visibleEdges.end();

        mapBlocks[i].SetBorders(left, right, top, bottom);
    }
}

// void Gameplay::SpawnUpdateThrowable(ThrowableID_t id, ThrowableSpawnEventDto throwableData) {
//     if (throwables.contains(id)) {
//         throwables.at(id).SetTargetPos(throwableData.position);
//         return;
//     }

//     throwables.emplace(id, ThrowableRenderer(throwableData.type, throwableData.position));
// }
// void Gameplay::DespawnThrowable(ThrowableID_t id) { throwables.erase(id); }


void Gameplay::UpdateGame(const Snapshot& snapshot) {
    for (size_t i = 0; i < snapshot.raycastsEvents.size(); i++) {
        auto ray = snapshot.raycastsEvents[i];
        bulletsController.SpawnBullet(ray);
    }

    ducksController.UpdateEvents(snapshot.updates);

    for (const auto& it: snapshot.collectableSpawns) {
        std::cout << "Collectable spawn\n";
        collectablesController.SpawnCollectable(it);
    }
    for (const auto& it: snapshot.collectableDespawns) {
        std::cout << "Collectable Despawn\n";
        collectablesController.DespawnCollectable(it);
    }

    for (const auto& it: snapshot.throwableSpawns) {
        std::cout << "Throwable spawn/update\n";
        throwablesController.SpawnUpdateThrowable(it.first, it.second);
    }
    for (const auto& it: snapshot.throwableDespawns) {
        std::cout << "Throwable Despawn\n";
        throwablesController.DespawnThrowable(it);
    }
}

void Gameplay::TakeSnapshots(Callback OnLastSnapshot) {
    shared_ptr<Snapshot> snapshot;
    while (!finishing && client.TryRecvNetworkMsg(snapshot)) {
        UpdateGame(*snapshot);

        // Check if last snapshot...
        if (snapshot->gameOver) {
            OnLastSnapshot();
            finishing = true;
        }
    }
}

void Gameplay::DrawGameWorld(float deltaTime) {
    mapBg.Draw(cam);

    for (auto& it: mapBlocks) {
        it.Draw(cam);
    }

    bulletsController.Draw(deltaTime, cam);
    throwablesController.Draw(deltaTime, cam);

    collectablesController.Draw(cam);

    ducksController.Draw(deltaTime, cam);
}

void Gameplay::InitGUI() {

    PlayerData localPlayerData = ducksController.GetLocalPlayerData();
    gui.InitPlayer1GUI(DUCK_SKIN_COLORS.at(localPlayerData.playerSkin), localPlayerData.nickname);

    auto secondLocalPlayerData = ducksController.GetLocalSecondPlayerData();
    if (secondLocalPlayerData.has_value()) {
        gui.InitPlayer2GUI(DUCK_SKIN_COLORS.at(secondLocalPlayerData.value().playerSkin),
                           secondLocalPlayerData.value().nickname);
    }
}

Gameplay::Gameplay(Client& cl, GameKit& gameKit, bool& wasClosed, MatchStartDto matchData,
                   GameSceneDto mapData, Snapshot firstSnapshot, bool isInitial):
        BaseScreen(gameKit, wasClosed),
        client(cl),
        isInitial(isInitial),
        camController(gameKit.GetCamera()),
        mapBg("bg_forest.png", Transform(Vector2D::Zero(), Vector2D(300, 300))),
        fadePanel(RectTransform(Transform(Vector2D(0, 0), Vector2D(2000, 2000))),
                  ColorExtension::Black().SetAlpha(0), 20),
        fadePanelTween(fadePanel, ColorExtension::Black().SetAlpha(255), 0.6f,
                       [this]() { running = false; }),
        controls(this->client),
        resourceManager(gameKit.GetResourceManager()),
        audioManager(gameKit.GetAudioManager()),
        throwablesController(resourceManager),
        collectablesController(resourceManager),
        bulletsController(resourceManager, audioManager),
        ducksController(client.GetLocalID(), camController, resourceManager, audioManager) {

    InitPlayers(matchData, firstSnapshot);
    InitMap(mapData);

    controls.SetSecondPlayer(ducksController.HasSecondPlayer());

    string themeMusic = resourceManager.GetMapThemeData(mapData.theme).bgMusicFile;
    audioManager.PlayMusic(themeMusic);

    UpdateGame(firstSnapshot);
    InitGUI();
}

Gameplay::~Gameplay() { audioManager.StopMusic(); }

void Gameplay::TakeInput(SDL_Event event) {
    if (finishing)
        return;
    if (!showColorsPanel.HasFinished()) {
        return;
    }

    controls.TakeInputEvent(event);
}


void Gameplay::InitRun() {
    finishing = false;
    camController.Reset();
    if (isInitial) {
        showColorsPanel.Show(ducksController.GetPlayersData(), resourceManager.GetDuckData());
    }
}

void Gameplay::Update(float deltaTime) {
    if (!showColorsPanel.HasFinished()) {
        showColorsPanel.Update(deltaTime);
    } else {
        TakeSnapshots([this]() { fadePanelTween.Play(); });
    }

    camController.Update(deltaTime);
    TweenManager::GetInstance().Update(deltaTime);

    bulletsController.ReapDead();

    DrawGameWorld(deltaTime);
    GUIManager::GetInstance().Draw(cam);
}
