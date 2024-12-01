#include "Gameplay.h"

void Gameplay::InitPlayers(const MatchStartDto& matchData, const Snapshot& firstSnapshot) {
    Vector2D duckSize = matchData.duckSize;
    playersData = matchData.playersData;

    for (auto& pData: playersData) {
        if (firstSnapshot.updates.find(pData.playerID) == firstSnapshot.updates.end())
            continue;
        Vector2D spawnPos = firstSnapshot.updates.at(pData.playerID).motion;
        PlayerEvent initialEvent = firstSnapshot.updates.at(pData.playerID);

        players.emplace(pData.playerID,
                        std::make_shared<DuckClientRenderer>(Transform(spawnPos, duckSize), pData,
                                                             initialEvent, camController));
    }
}

void Gameplay::InitMap(GameSceneDto mapData) {
    for (size_t i = 0; i < mapData.groundBlocks.size(); i++) {
        auto groundData = mapData.groundBlocks[i];
        mapBlocks.emplace_back("tile_set.png", "tile_set.yaml", groundData.mySpace, 4);

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

void Gameplay::BulletsReapDead() {
    bullets.remove_if([](BulletRenderer c) { return !c.IsAlive(); });
}

void Gameplay::SpawnCollectable(CollectableSpawnEventDto collectableData) {
    collectables.emplace(collectableData.id,
                         CollectableRenderer(collectableData.type, collectableData.position));
}
void Gameplay::DespawnCollectable(CollectableID_t id) { collectables.erase(id); }


void Gameplay::SpawnUpdateThrowable(ThrowableID_t id, ThrowableSpawnEventDto throwableData) {
    if (throwables.contains(id)) {
        throwables.at(id).SetTargetPos(throwableData.position);
        return;
    }

    throwables.emplace(id, ThrowableRenderer(throwableData.type, throwableData.position));
}
void Gameplay::DespawnThrowable(ThrowableID_t id) { throwables.erase(id); }


void Gameplay::UpdateGame(const Snapshot& snapshot) {
    for (size_t i = 0; i < snapshot.raycastsEvents.size(); i++) {
        auto ray = snapshot.raycastsEvents[i];
        bullets.emplace_back(ray.type, ray.origin, ray.end, 100);
        AudioManager::GetInstance().PlayShootSFX(ray.type);
    }

    for (const auto& it: snapshot.updates) {
        players[it.first]->SetEventTarget(it.second);
    }

    for (const auto& it: snapshot.collectableSpawns) {
        std::cout << "Collectable spawn\n";
        SpawnCollectable(it);
    }
    for (const auto& it: snapshot.collectableDespawns) {
        std::cout << "Collectable Despawn\n";
        DespawnCollectable(it);
    }

    for (const auto& it: snapshot.throwableSpawns) {
        std::cout << "Throwable spawn/update\n";
        SpawnUpdateThrowable(it.first, it.second);
    }
    for (const auto& it: snapshot.throwableDespawns) {
        std::cout << "Throwable Despawn\n";
        DespawnThrowable(it);
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

    for (auto& it: bullets) {
        it.Update(deltaTime);
        it.Draw(cam);
    }

    for (auto& it: collectables) {
        it.second.Draw(cam);
    }

    for (auto& it: throwables) {
        it.second.Update(deltaTime);
        it.second.Draw(cam);
    }

    for (const auto& it: players) {
        auto data = it.second;
        data->Update(deltaTime);
        data->Draw(cam);
    }
}

void Gameplay::InitGUI() {
    uint16_t localConnectionId = client.GetLocalID();

    bool isPlayer1 = true;
    for (uint8_t i = 0; i < (uint8_t)players.size(); i++) {
        auto playerId = PlayerIdentifier::GeneratePlayerID(localConnectionId, i);

        if (players.contains(playerId)) {
            Color color = players[playerId]->GetSkinColor();
            std::string nickname = players[playerId]->GetNickname();
            if (isPlayer1) {
                gui.InitPlayer1GUI(color, nickname);
                isPlayer1 = false;
            } else {
                gui.InitPlayer2GUI(color, nickname);
            }
        }
    }
}

Gameplay::Gameplay(Client& cl, Camera& c, bool& wasClosed, MatchStartDto matchData,
                   GameSceneDto mapData, Snapshot firstSnapshot, bool isInitial):
        BaseScreen(c, wasClosed),
        client(cl),
        isInitial(isInitial),
        camController(c),
        mapBg("bg_forest.png", Transform(Vector2D::Zero(), Vector2D(300, 300))),
        fadePanel(RectTransform(Transform(Vector2D(0, 0), Vector2D(2000, 2000))),
                  ColorExtension::Black().SetAlpha(0), 10),
        fadePanelTween(fadePanel, ColorExtension::Black().SetAlpha(255), 0.6f,
                       [this]() { running = false; }),
        controls(this->client) {
    InitPlayers(matchData, firstSnapshot);
    InitMap(mapData);

    controls.SetSecondPlayer(
            players.contains(PlayerIdentifier::GeneratePlayerID(client.GetLocalID(), 1)));

    UpdateGame(firstSnapshot);
    InitGUI();
}
Gameplay::~Gameplay() = default;

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
        showColorsPanel.Show(players);
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

    BulletsReapDead();

    DrawGameWorld(deltaTime);
    GUIManager::GetInstance().Draw(cam);
}
