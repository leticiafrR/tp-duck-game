#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../data/command.h"
#include "../../data/dataTransferObjects.h"
#include "../../data/id.h"
#include "../../data/snapshot.h"

#include "types.h"

class GameWorld {
    std::vector<PlayerID_t> players;
    const std::string level;
    int procesedCmmds = 0;
    std::unordered_map<PlayerID_t, PlayerEvent> updates;
    Vector2D posicionInicial;

public:
    GameWorld(const std::string& scene, const std::vector<PlayerID_t>& playersIds):
            players(playersIds), level(scene) {}

    GameSceneDto getSceneDto() {
        std::vector<Transform> platform;
        Transform t;
        platform.push_back(t);

        std::vector<GroundDto> groundBlocks;
        std::set<GroundDto::VISIBLE_EDGES> edges;
        GroundDto g(t, edges);
        groundBlocks.push_back(g);

        GameSceneDto scene(level, platform, groundBlocks);
        return scene;
    }

    void HandleCommand(const Command& cmd) {
        std::cout << "Recibimos un comando del jugador: " << cmd.playerId << "\n";
        procesedCmmds++;
        posicionInicial.x += 1;
        // simulamos hacer que la posicion inicial se aumenta a la derecha
        PlayerEvent playerEvent;
        playerEvent.motion = posicionInicial;
        playerEvent.stateTransition = DuckState::RUNNING;
        playerEvent.flipping = Flip::Right;

        updates[cmd.playerId] = playerEvent;
    }

    void Update() { std::cout << "Tick del mundo del juego\n"; }

    bool HasWinner() {
        // paramos a los 5 comandos
        return procesedCmmds == 5;
    }

    PlayerID_t WhoWon() { return players[0]; }

    Snapshot GetSnapshot() {
        Snapshot snp(HasWinner(), updates);
        return snp;
    }

    // void quitPlayer(PlayerID_t);
    ~GameWorld() = default;
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
