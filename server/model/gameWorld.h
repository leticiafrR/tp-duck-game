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
#include "duck/duck.h"
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


    void jump(PlayerID_t id);
    void flutter(PlayerID_t id);  // if the duck is in the air
    void stoop(PlayerID_t id);    // get down
    void stopStooping(PlayerID_t id);
    void moveRight(PlayerID_t id);
    void moveLeft(PlayerID_t id);
    void stopMoving(PlayerID_t id);
    void lookUp(PlayerID_t id);
    void stopLookingUp(PlayerID_t id);

    void shoot(PlayerID_t id);  // to the current direction
    void stopShooting();
    void equipWeapon();
    void unequipWeapon();
    void createMap();

    //*******************************************
    void reapDead();
    void checkCollisions();

public:
    GameWorld();
    void handleCommand(const dataCommand& cmd);

    void addPlayers(const std::vector<PlayerID_t>& idsPlayers);
    Snapshot getSnapshot();
    void update();
    bool isGameOver();
};


void GameWorld::handleCommand(const dataCommand& cmd) {
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
