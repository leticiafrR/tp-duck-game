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
    // vector de jugadores (solo habrà uno)
    std::vector<PlayerID_t> players;
    const std::string level;

    int countTicks = 0;

    std::unordered_map<PlayerID_t, Vector2D> positions;

public:
    // recibimos dos jugadores
    GameWorld(const std::string& scene, const std::vector<PlayerID_t>& playersIds):
            players(playersIds), level(scene) {
        for (auto id: players) {
            positions[id] = Vector2D(0, 0);
        }
    }

    GameSceneDto getSceneDto() {
        std::vector<Transform> platform;
        Transform t;
        platform.push_back(t);

        std::vector<GroundDto> groundBlocks;
        GroundDto groundBlock(t, {VISIBLE_EDGES::BOTTOM, VISIBLE_EDGES::TOP});
        groundBlocks.push_back(groundBlock);

        GameSceneDto scene(level, platform, groundBlocks);
        return scene;
    }
    void showCommand(const Command& command) {
        std::cout << "      -MODELO Got command: \n         Player:" << command.playerId
                  << "\n         Command: " << FmtCmmd(command.cmd) << "\n";
    }
    void HandleCommand(const Command& command) {
        std::cout << "\n\n        ...processing command...\n";
        showCommand(command);
        if (command.cmd == CommandCode::MoveRight_KeyDown) {
            positions[command.playerId] =
                    Vector2D(positions[command.playerId].x + 1, positions[command.playerId].y);
        } else if (command.cmd == CommandCode::MoveLeft_KeyDown) {
            positions[command.playerId] =
                    Vector2D(positions[command.playerId].x - 1, positions[command.playerId].y);
        }
        std::cout << "\n      Ended procesing commands\n\n";
    }

    void Update() {
        std::cout << "      MODELO: The tick: " << countTicks << " inthe gameWorld has ended.\n";
        countTicks++;
    }

    bool HasWinner() {
        // paramos solo 10 ticks
        return countTicks == 20;
    }

    PlayerID_t WhoWon() { return players[0]; }

    Snapshot GetSnapshot() {
        bool hayGanador = HasWinner();

        std::unordered_map<PlayerID_t, PlayerEvent> updates;

        for (auto pair: positions) {
            PlayerEvent event{positions[pair.first], DuckState::IDLE, Flip::Up};
            updates[pair.first] = event;
        }

        Snapshot snp(hayGanador, updates);
        // std::cout << "\nMODELO: Snapshot del tick " << countTicks << " :\n";
        // std::cout << "-GaveOver? " << hayGanador << "; \n -Playermotion: "
        //           << "x:" << snp.updates[players[0]].motion.x
        //           << " y:" << snp.updates[players[0]].motion.y << "\n";
        // std::cout << "\n";

        std::cout << "\n[GameUpdate] :\n";
        // std::cout << "-> tick: "
        std::cout << "-> gameOver: " << (snp.gameOver ? "true" : "false") << "\n";
        int i = 1;
        for (auto it = snp.updates.begin(); it != snp.updates.end(); it++) {
            std::cout << "->update " << i << " avo: "
                      << "\n   PlayerID:" << (int)it->first << "\n     POS:" << it->second.motion.x
                      << "," << it->second.motion.y << "\n";
            i++;
        }
        return snp;
    }

    std::string FmtCmmd(CommandCode cmdCode) {
        switch (cmdCode) {
            case CommandCode::MoveRight_KeyDown:
                return "Move Right";
                break;

            case CommandCode::MoveLeft_KeyDown:
                return "Move Left";
                break;

            default:
                return "Another cmmd";
        }
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
