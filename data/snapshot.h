#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <cstdint>
#include <unordered_map>

#include "../common/Vector2D.h"

#include "id.h"

/******************************GAME UPDATING DATA************************************/

struct DuckUpdate {
    typedef enum: uint8_t { RIGHT, LEFT, UP } FLIP;
    typedef enum: uint8_t { IDLE = 1, JUMP, FALLING, RUNNING, DEAD } DUCK_STATUS;
    Vector2D position;
    DUCK_STATUS status;
    FLIP flip;
};

struct Snapshot {
    bool gameEnded;
    // skiping the part  of making a player quit out of the game
    // std::vector<PlayerID_t> quiters;
    std::unordered_map<PlayerID_t, DuckUpdate> ducksUpdate;

    // cppcheck-suppress passedByValue
    Snapshot(bool gameEnded, std::unordered_map<PlayerID_t, DuckUpdate> ducksUpdate):
            gameEnded(gameEnded), ducksUpdate(ducksUpdate) {}
};

#endif
