#include "Game.h"

#include "data/command.h"

GameWorld::GameWorld(const Vector2D& posToTest, const std::vector<PlayerID_t>& playersIds,
                     const std::string& sceneName):
        livePlayers(playersIds.size()) {
    eventsManager.SendInstantProjectileListener(p);
    std::cout << "welcom to " << sceneName << std::endl;

    if (std::isinf(posToTest.x)) {
        CreatePlayers(playersIds);
    } else {
        /**
         * for testing, call like: GameWorld game = GameWorld(Vector2D(16, -13));
         * the game'll create a *unique duck* with id 1 in the position indicated (maybe corrected
         * by applying gravity (once at the start)).
         */

        Testing(posToTest);
    }
    eventsManager.SendPlayersListeners(players);
}

GameWorld::~GameWorld() {
    for (const auto& pair: players) {
        delete pair.second;
    }
    players.clear();
}

void GameWorld::CreatePlayers(const std::vector<PlayerID_t>& playersIds) {
    std::vector<Vector2D> spawnPoints = map.GetPlayersSpawnPoints();
    for (size_t i = 0; i < playersIds.size(); i++) {
        players[playersIds[i]] = new Duck(spawnPoints[i], p);
    }
}

void GameWorld::Update(float deltaTime) {
    p.Update(map, players);
    for (auto& pair: players) {
        pair.second->Update(map, deltaTime);
    }
    ReapDead();
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
    if (players.contains(cmmd.playerId)) {
        ExecCommand(players[cmmd.playerId], cmmd.cmd);
    } else {
        std::cout << "[GAME WORLD]: tratas de mover un jugador muerto\n";
    }
}

void GameWorld::ExecCommand(Duck* player, const CommandCode& code) {
    switch (code) {
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
        case CommandCode::Jump:
            player->TryJump();
            break;
        case CommandCode::UseItem_KeyDown:
            std::cout << "[game:execCommand] try useItem\n";
            player->TryUseItem();

            break;
        case CommandCode::UseItem_KeyUp:
            player->StopUseItem();
            break;
        default:
            break;
    }
}

GameSceneDto GameWorld::getSceneDto() { return map.GetScene(); }

Snapshot GameWorld::GetSnapshot() { return eventsManager.GetSnapshot(IsOver()); }

PlayerID_t GameWorld::WhoWon() { return players.begin()->first; }

bool GameWorld::IsOver() { return livePlayers <= 1; }

void GameWorld::Testing(const Vector2D& posToTest) {
    std::cout << "[TESTING]: Receiving unique player [" << ID_PLAYER_UNIQUE_TEST
              << "]. Spawned in:(" << posToTest.x << "," << posToTest.y << ")\n";
    players[ID_PLAYER_UNIQUE_TEST] = new Duck(posToTest, p);
}
