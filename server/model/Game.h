#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../data/command.h"
#include "event/EventsManager.h"
#include "map/staticMap.h"

#include "Duck.h"

class GameWorld {
private:
    size_t livePlayers;
    StaticMap map;
    std::unordered_map<PlayerID_t, Duck*> players;
    std::set<ObjectID_t> uniquesIds;
    EventsManager eventsManager;
    void ReapDead();

public:
    explicit GameWorld(const Vector2D& posToTest = Vector2D::Zero(),
                       const std::vector<PlayerID_t>& playersIds = {1},
                       const std::string& sceneName = "");
    void HandleCommand(const Command& cmd);
    void Update(float deltaTime);
    bool HasWinner();
    bool IsOver();
    PlayerID_t WhoWon();
    Snapshot GetSnapshot();
    // void quitPlayer(PlayerID_t);
    ~GameWorld();
};


/**********************************************************************************
 *                              DEFINITIONS
 ***********************************************************************************/


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

GameWorld::GameWorld(const Vector2D& posToTest, const std::vector<PlayerID_t>& playersIds,
                     const std::string& sceneName):
        livePlayers(playersIds.size()), uniquesIds(playersIds.begin(), playersIds.end()) {

    if (posToTest.IsFarFrom(Vector2D::Zero())) {
        players[1] = new Duck(posToTest);
    } else {
        std::vector<Vector2D> spawnPoints = map.GetPlayersSpawnPoints();
        for (size_t i = 0; i < spawnPoints.size(); i++) {
            std::cout << "Welcome to: " << sceneName << "\n";
            players[playersIds[i]] = new Duck(spawnPoints[i]);
        }
    }

    eventsManager.SendListeners(players);
}

GameWorld::~GameWorld() {
    for (auto& pair: players) {
        delete pair.second;
    }
    players.clear();
}

void GameWorld::ReapDead() {
    for (auto it = players.begin(); it != players.end();) {
        if (it->second->IsDead()) {
            // std::cout << "muriò el jugador con ID: [" << it->first << "]\n";
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
#endif
