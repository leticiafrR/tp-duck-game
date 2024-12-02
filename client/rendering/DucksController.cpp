#include "DucksController.h"

DucksController::DucksController(uint16_t connectionId, CameraController& cameraController,
                                 ResourceManager& resourceManager, AudioManager& audioManager):
        cameraController(cameraController),
        resourceManager(resourceManager),
        audioManager(audioManager),
        connectionId(connectionId) {}

DucksController::~DucksController() = default;

PlayerData DucksController::GetLocalPlayerData() const { return playersDataMap.at(localPlayerId); }

std::optional<PlayerData> DucksController::GetLocalSecondPlayerData() const {
    if (localSecondPlayerId.has_value())
        return playersDataMap.at(localSecondPlayerId.value());

    return std::nullopt;
}

unordered_map<PlayerID_t, PlayerData> DucksController::GetPlayersData() const {
    return playersDataMap;
}

bool DucksController::HasSecondPlayer() { return localSecondPlayerId.has_value(); }

PlayerData DucksController::GetPlayerData(PlayerID_t playerId) {
    return playersDataMap.at(playerId);
}

void DucksController::SpawnPlayers(Vector2D duckSize, vector<PlayerData> playersData,
                                   unordered_map<PlayerID_t, PlayerEvent> initialEvents) {

    for (auto& pData: playersData) {
        playersDataMap.emplace(pData.playerID, pData);
        players.emplace(pData.playerID, std::make_shared<DuckClientRenderer>(
                                                duckSize, DUCK_SKIN_COLORS.at(pData.playerSkin),
                                                resourceManager, cameraController));
    }

    SetLocals();
    UpdateEvents(initialEvents, true);
}

void DucksController::SetLocals() {
    bool lookForSecond = false;
    for (auto& player: players) {
        uint16_t connectionId;
        uint8_t iPlayer;
        PlayerIdentifier::DecomposePlayerID(player.first, connectionId, iPlayer);

        if (this->connectionId == connectionId) {
            if (!lookForSecond) {
                localPlayerId = player.first;
                lookForSecond = true;
            } else {
                localSecondPlayerId = player.first;
                break;
            }
        }
    }
}


void DucksController::UpdateEvents(std::unordered_map<PlayerID_t, PlayerEvent> events,
                                   bool initial) {

    for (auto playerEvent: events) {
        if (!players.contains(playerEvent.first))
            continue;
        players[playerEvent.first]->SetEventTarget(playerEvent.second, resourceManager,
                                                   audioManager, initial);
    }
}
void DucksController::Draw(float deltaTime, Camera& cam) {
    for (const auto& it: players) {
        auto data = it.second;
        data->Update(deltaTime);
        data->Draw(cam);
    }
}
