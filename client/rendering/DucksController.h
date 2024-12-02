#ifndef DUCKS_CONTROLLER_H
#define DUCKS_CONTROLLER_H

#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

#include "client/Framework.h"
#include "common/playerIdentifier.h"

#include "DuckClientRenderer.h"

using std::shared_ptr;
using std::unordered_map;
using std::vector;

class DucksController {
private:
    CameraController& cameraController;
    ResourceManager& resourceManager;
    AudioManager& audioManager;

    uint16_t connectionId;

    PlayerID_t localPlayerId;
    std::optional<PlayerID_t> localSecondPlayerId;

    unordered_map<PlayerID_t, PlayerData> playersDataMap;
    unordered_map<PlayerID_t, std::shared_ptr<DuckClientRenderer>> players;

public:
    DucksController(uint16_t connectionId, CameraController& cameraController,
                    ResourceManager& resourceManager, AudioManager& audioManager);
    ~DucksController();

    void SpawnPlayers(Vector2D duckSize, vector<PlayerData> playersData,
                      unordered_map<PlayerID_t, PlayerEvent> initialEvents);

    void UpdateEvents(unordered_map<PlayerID_t, PlayerEvent> events, bool initial = false);
    void Draw(float deltaTime, Camera& cam);

    bool HasSecondPlayer();

    void SetLocals();
    PlayerData GetPlayerData(PlayerID_t playerId);

    unordered_map<PlayerID_t, PlayerData> GetPlayersData() const;

    PlayerData GetLocalPlayerData() const;
    std::optional<PlayerData> GetLocalSecondPlayerData() const;
};

#endif
