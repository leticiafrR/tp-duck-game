#ifndef SNAPSHOT_DTA_H
#define SNAPSHOT_DTA_H
#include <unordered_map>

#include "common/Vector2D.h"

#include "id.h"
#include "networkMsg.h"

enum class Flip : uint8_t { Left = 1, Right, Up };
enum class TypeBullet : uint8_t { RayoLaser, Banana, GranadaFragment };
enum class DuckState : uint8_t { IDLE = 1, JUMPING, FALLING, RUNNING, WOUNDED, DEAD };

struct PlayerEvent {
    Vector2D motion;
    // cppcheck-suppress unusedStructMember
    DuckState stateTransition;
    // cppcheck-suppress unusedStructMember
    Flip flipping;
};

struct Snapshot: public NetworkMsg {
    bool gameOver;
    std::unordered_map<PlayerID_t, PlayerEvent> updates;
    Snapshot(bool _gameOver, const std::unordered_map<PlayerID_t, PlayerEvent>& _updates):
            gameOver(_gameOver), updates(_updates) {}
};

#endif
