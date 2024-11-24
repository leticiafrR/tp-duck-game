#include "Game.h"

#include "data/command.h"

GameWorld::GameWorld(const std::vector<PlayerID_t>& playersIds, const std::string& sceneName,
                     const Config& conf):
        livePlayers(playersIds.size()), map(sceneName) {
    eventsManager.SendInstantProjectileListener(p);
    std::cout << "welcom to " << sceneName << std::endl;
    CreatePlayers(playersIds, conf);
    eventsManager.SendPlayersListeners(players);
}

GameWorld::~GameWorld() {
    for (const auto& pair: players) {
        delete pair.second;
    }
    players.clear();
}

void GameWorld::CreatePlayers(const std::vector<PlayerID_t>& playersIds, const Config& conf) {
    std::vector<Vector2D> spawnPoints = map.GetPlayersSpawnPoints();
    for (size_t i = 0; i < playersIds.size(); i++) {
        std::cout << "CreatPlayers" << std::endl;
        players[playersIds[i]] = new Duck(spawnPoints[i], playersIds[i], p, conf);
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
        ExecCommand(players[cmmd.playerId], cmmd.code);
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
            player->TryUseItem();
            break;
        case CommandCode::UseItem_KeyUp:
            player->StopUseItem();
            break;
        case CommandCode::LookUp_KeyDown:
            player->LookUp();
            break;
        case CommandCode::LookUp_KeyUp:
            player->StopLookUp();
            break;
        case CommandCode::Crouch_KeyDown:
            player->Crouch();
            break;
        case CommandCode::Crouch_KeyUp:
            player->StopCrouch();
            break;
        default:
            break;
    }
}

GameSceneDto GameWorld::getSceneDto() { return map.GetScene(); }

Snapshot GameWorld::GetSnapshot() { return eventsManager.GetSnapshot(IsOver()); }

PlayerID_t GameWorld::WhoWon() { return players.begin()->first; }

bool GameWorld::IsOver() { return livePlayers <= 1; }
