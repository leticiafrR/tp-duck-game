#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <cstdint>
#include <unordered_map>
#include <vector>

#include "../../common/Collision.h"
#include "../../common/dataCommand.h"  //  for COMMAND
#include "../../data/id.h"
#include "/ammo/ammo.h"
#include "/weapon/weapon.h"
#include "/duck/duck.h"
// #include "/data/duckData.h"
#include "gameMap.h"
// represents a round
class GameWorld {
private:
    std::unordered_map<PlayerID_t, Duck*> players;
    std::unordered_map<ObjectID_t, Weapon*> weapons;
    std::unordered_map<ObjectID_t, Ammo*> ammos;
    std::unordered_map<ObjectID_t, SpawnPlace*> spawnPlaces;
    std::unordered_map<ObjectID_t, Box*> boxes;
    std::vector<StaticObjects*> staticObjects;  // walls, plattaforms
    bool isGameOver;
    void ReapDead();
    void CheckCollisions();

public:
    GameWorld();
    void HandleCommand(const dataCommand& cmd);
    void AddPlayers(const std::vector<PlayerID_t>& idsPlayers);
    Snapshot GetSnapshot();
    void Update();
    bool IsGameOver();
};

GameWorld::GameWorld(): isGameOver(false) {}
GameWorld::IsGameOver(): { return isGameOver; }

void GameWorld::HandleCommand(const dataCommand& cmd) {
    Duck* player = players[cmd.playerID];
    switch (cmd.commandID) {
        case CommandID::MoveLeft:
            player->MoveRight();
            break;
        case CommandID::MoveRight:
            player->MoveLeft();
            break;
        case CommandID::StopMoving:
            player->StopMoving();
            break;
            //---------------------------------------------------------------
        case CommandID::LookUp:
            player->LookUp();
            break;
        case CommandID::StopLookingkUp:
            player->StopLookingUp();
            break;
        case CommandID::Shoot:
            player->Shoot();
            break;
        case CommandID::StopShooting:
            player->ShootShooting();
            break;
        case CommandID::Jump:
            player->Jump();
            break;
        case CommandID::EquipWeapon:
            player->EquipWeapon();
            break;
        case CommandID::UnequipWeapon:
            player->UnequipWeapon();
            break;
        default:
            break;
    }
}
#endif
