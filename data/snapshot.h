#ifndef SNAPSHOT_DTA_H
#define SNAPSHOT_DTA_H

#include <unordered_map>
#include <vector>

#include "common/Vector2D.h"

#include "id.h"
#include "networkMsg.h"

enum class Flip : uint8_t { Left = 1, Right };
enum class TypeProjectile : uint8_t { RayoLaser, Bullet, Banana, GranadaFragment };
enum class DuckState : uint8_t {
    IDLE = 1,
    JUMPING,
    FALLING,
    RUNNING,
    WOUNDED,
    DEAD,
    DEAD_BY_FALLING
};
enum class TypeCollectable : uint8_t { EMPTY, COWBOY_PISTOL, LASER_RIFLE, HELMET, ARMOR };

struct PlayerEvent {
    Vector2D motion;
    DuckState stateTransition;
    Flip flipping;
    bool isLookingUp;
    TypeCollectable typeOnHand;
    bool isCrouched;

    PlayerEvent(const Vector2D& _motion, DuckState _stateTransition, Flip _flipping,
                bool _isLookingUp):
            motion(_motion),
            stateTransition(_stateTransition),
            flipping(_flipping),
            isLookingUp(_isLookingUp),
            typeOnHand(TypeCollectable::EMPTY),
            isCrouched(false) {}

    PlayerEvent(const Vector2D& _motion, DuckState _stateTransition, Flip _flipping,
                bool _isLookingUp, TypeCollectable _typeOnHand, bool _isCrouched):
            motion(_motion),
            stateTransition(_stateTransition),
            flipping(_flipping),
            isLookingUp(_isLookingUp),
            typeOnHand(_typeOnHand),
            isCrouched(_isCrouched) {}
};

// enum class DuckState : uint8_t { IDLE = 1, JUMPING, FALLING, RUNNING, DEAD};
// enum class DamageState : uint8_t {NO_DAMAGE,BULLET};

// struct PlayerEvent {
//     Vector2D motion;
//     DuckState stateTransition;
//     Flip flipping;
//     DamageState damageState
// };

struct InstantProjectileEventDto {
    TypeProjectile type;
    Vector2D origin;
    Vector2D end;

    InstantProjectileEventDto(TypeProjectile type, const Vector2D& origin, const Vector2D& end):
            type(type), origin(origin), end(end) {}
};

struct Snapshot: public NetworkMsg {
    bool gameOver;
    std::unordered_map<PlayerID_t, PlayerEvent> updates;
    std::vector<InstantProjectileEventDto> raycastsEvents;

    Snapshot(bool gameOver, const std::unordered_map<PlayerID_t, PlayerEvent>& updates,
             std::vector<InstantProjectileEventDto>& raycastsEvents):
            gameOver(gameOver), updates(updates), raycastsEvents(raycastsEvents) {}

    Snapshot(bool gameOver, const std::unordered_map<PlayerID_t, PlayerEvent>& updates):
            gameOver(gameOver), updates(updates) {}
};

#endif
