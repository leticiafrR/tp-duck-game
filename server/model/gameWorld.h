#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../data/command.h"
#include "../../data/dataTransferObjects.h"
#include "../../data/snapshot.h"

#include "types.h"
// #include "event/EventsManager.h"

// #include "Duck.h"
// #include "staticMap.h"

class GameWorld {
private:
    // size_t livePlayers;
    // StaticMap map;
    // std::unordered_map<PlayerID_t, Duck*> players;
    // std::set<ObjectID_t> uniquesIds;
    // EventsManager eventsManager;
    // void ReapDead();

public:
    explicit GameWorld(const std::vector<PlayerID_t>& playersIds, const std::string& sceneName);
    GameSceneDto getSceneDto();

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


// Snapshot GameWorld::GetSnapshot() {
//     // return eventsManager.GetSnapshot(IsOver());
// }

// bool GameWorld::IsOver() {
//     // return livePlayers == 0;
// }

// bool GameWorld::HasWinner() {
//     return false;
//     // return livePlayes == 1;
// }

// PlayerID_t GameWorld::WhoWon() {
//     // return players.begin()->first;
// }

// void GameWorld::Update(float deltaTime) {
//     // for (auto& pair: players) {
//     //     Duck* player = pair.second;
//     //     player->Update(map, deltaTime);
//     //     // player->UpdatePosition(map, deltaTime);
//     // }
//     // ReapDead();
// }

// GameWorld::GameWorld(const std::vector<PlayerID_t>& playersIds, const std::string& sceneName):
//         livePlayers(playersIds.size()), uniquesIds(playersIds.begin(), playersIds.end()) {

//     // std::vector<Vector2D> spawnPoints = map.GetPlayersSpawnPoints();
//     // for (size_t i = 0; i < spawnPoints.size(); i++) {
//     //     std::cout << "Welcome to: " << sceneName << "\n";
//     //     PlayerID_t id = playersIds[i];
//     //     Vector2D pos = spawnPoints[i];
//     //     players[id] = new Duck(pos);
//     //     std::cout << "se creò al jugador [" << id << "] con posiciòn: (" << pos.x << "," <<
//     pos.y
//     //               << ")\n";
//     // }
//     // eventsManager.SendListeners(players);
// }

// GameWorld::~GameWorld() {
//     for (auto& pair: players) {
//         delete pair.second;
//     }
//     players.clear();
// }

// // void GameWorld::ReapDead() {
// //     for (auto it = players.begin(); it != players.end();) {
// //         if (it->second->IsDead()) {
// //             std::cout << "muriò el jugador con ID: [" << it->first << "]\n";
// //             delete it->second;
// //             it = players.erase(it);
// //             livePlayers--;
// //         } else {
// //             ++it;
// //         }
// //     }
// // }

// void GameWorld::HandleCommand(const Command& cmmd) {
//     // Duck* player = players[cmmd.playerId];
//     // switch (cmmd.cmd) {
//     //     case CommandCode::MoveLeft_KeyDown:
//     //         player->TryMoveLeft();
//     //         break;
//     //     case CommandCode::MoveLeft_KeyUp:
//     //         player->StopMoveLeft();
//     //         break;
//     //     case CommandCode::MoveRight_KeyDown:
//     //         player->TryMoveRight();
//     //         break;
//     //     case CommandCode::MoveRight_KeyUp:
//     //         player->TryMoveRight();
//     //         break;
//     //     default:
//     //         break;
//     // }
// }
#endif
