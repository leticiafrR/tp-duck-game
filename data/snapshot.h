#ifndef SNAPSHOT_DTA_H
#define SNAPSHOT_DTA_H

#include <unordered_map>
#include <vector>

#include "common/Vector2D.h"

#include "id.h"
#include "networkMsg.h"

enum class Flip : uint8_t { Left = 1, Right };
enum class TypeProjectile : uint8_t { LASER, BULLET, BANANA, FRAGMENT };
enum class DuckState : uint8_t {
    IDLE = 1,
    JUMPING,
    FALLING,
    RUNNING,
    WOUNDED,
    DEAD,
    DEAD_BY_FALLING
};
enum class TypeCollectable : uint8_t {
    EMPTY,
    COWBOY_PISTOL,
    LASER_RIFLE,
    PEW_PEW_LASER,
    SHOTGUN,
    SNIPER,
    DUELING_PISTOL,
    AK47,
    MAGNUM,
    HELMET,
    ARMOR
};

struct PlayerEvent {
    Vector2D motion;
    DuckState stateTransition;
    Flip flipping;
    bool isLookingUp;
    TypeCollectable typeOnHand;
    bool isCrouched;
    bool cuacking;

    PlayerEvent() = default;

    PlayerEvent(const Vector2D& _motion, DuckState _stateTransition, Flip _flipping,
                bool _isLookingUp, TypeCollectable _typeOnHand, bool _isCrouched,
                bool _cuacking = false):
            motion(_motion),
            stateTransition(_stateTransition),
            flipping(_flipping),
            isLookingUp(_isLookingUp),
            typeOnHand(_typeOnHand),
            isCrouched(_isCrouched),
            cuacking(_cuacking) {}
};

struct InstantProjectileEventDto {
    TypeProjectile type;
    Vector2D origin;
    Vector2D end;

    InstantProjectileEventDto() = default;
    InstantProjectileEventDto(TypeProjectile type, const Vector2D& origin, const Vector2D& end):
            type(type), origin(origin), end(end) {}
};

struct CollectableDespawnEventDto {
    CollectableID_t id;
    explicit CollectableDespawnEventDto(CollectableID_t _id): id(_id) {}
    CollectableDespawnEventDto() = default;
};

struct CollectableSpawnEventDto {
    CollectableID_t id;
    Vector2D position;
    TypeCollectable type;

    CollectableSpawnEventDto(CollectableID_t _id, const Vector2D& _position, TypeCollectable _type):
            id(_id), position(_position), type(_type) {}
    CollectableSpawnEventDto() = default;
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
