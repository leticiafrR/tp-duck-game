#include "Game.h"

#include "../../data/command.h"
/* Players generators **************************************************************/

void GameWorld::Testing(const Vector2D& posToTest) {
    std::cout << "[TESTING]: Receiving unique player [" << ID_PLAYER_UNIQUE_TEST
              << "]. Spawned in:(" << posToTest.x << "," << posToTest.y << ")\n";
    players[ID_PLAYER_UNIQUE_TEST] = new Duck(posToTest);
}

void GameWorld::CreatePlayers(const std::vector<PlayerID_t>& playersIds) {
    std::vector<Vector2D> spawnPoints = map.GetPlayersSpawnPoints();
    for (size_t i = 0; i < spawnPoints.size(); i++) {
        PlayerID_t id = playersIds[i];
        Vector2D pos = spawnPoints[i];
        std::cout << "Receiving player [" << id << "]. Spawned in:(" << pos.x << "," << pos.y
                  << ")\n";
        players[id] = new Duck(pos);
    }
}

/**
 * for testing, call like: GameWorld game = GameWorld(Vector2D(16, -13));
 * the game'll create a *unique duck* with id 1 in the position indicated (maybe corrected by
 * applying gravity (once at the start)).
 */
GameWorld::GameWorld(const Vector2D& posToTest, const std::vector<PlayerID_t>& playersIds,
                     const std::string& sceneName):
        livePlayers(playersIds.size()), uniquesIds(playersIds.begin(), playersIds.end()) {
    std::cout << "Welcome to: " << sceneName << "\n";
    if (std::isinf(posToTest.x)) {
        CreatePlayers(playersIds);
    } else {
        Testing(posToTest);
    }
    eventsManager.SendListeners(players);
}


/* Game's logic **************************************************************/
GameSceneDto GameWorld::getSceneDto() { return map.GetScene(); }

Snapshot GameWorld::GetSnapshot() { return eventsManager.GetSnapshot(IsOver()); }

bool GameWorld::IsOver() { return livePlayers == 0; }

bool GameWorld::HasWinner() {
    return false;
    // return livePlayes == 1;
}

PlayerID_t GameWorld::WhoWon() { return players.begin()->first; }

void GameWorld::Update(float deltaTime) {
    for (auto& pair: players) {
        pair.second->Update(map, deltaTime);
    }
    ReapDead();
}


GameWorld::~GameWorld() {
    for (const auto& pair: players) {
        delete pair.second;
    }
    players.clear();
}

void GameWorld::ReapDead() {
    for (auto it = players.begin(); it != players.end();) {
        if (it->second->IsDead()) {
            std::cout << "muriò el jugador con ID: [" << it->first << "]\n";
            delete it->second;
            it = players.erase(it);
            livePlayers--;
        } else {
            ++it;
        }
    }
}

void GameWorld::HandleCommand(const Command& cmmd) {
    Duck* player = players[cmmd.playerId];
    switch (cmmd.cmd) {
        case CommandCode::MoveLeft_KeyDown:
            player->TryMoveLeft();
            break;
        case CommandCode::MoveLeft_KeyUp:
            player->StopMoveLeft();
            break;
        case CommandCode::MoveRight_KeyDown:
            player->TryMoveRight();
            break;
        case CommandCode::MoveRight_KeyUp:
            player->StopMoveRight();
            break;
        default:
            break;
    }
}
