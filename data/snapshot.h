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
    ARMOR,
    __typesCount  // always at the end
};

struct PlayerEvent {
    Vector2D motion;
    DuckState stateTransition;
    Flip flipping;
    bool isLookingUp;
    TypeCollectable typeOnHand;
    bool isCrouched;
    bool cuacking;
    bool hasArmor;
    bool hasHelmet;

    PlayerEvent() = default;

    PlayerEvent(const Vector2D& _motion, DuckState _stateTransition, Flip _flipping,
                bool _isLookingUp, TypeCollectable _typeOnHand, bool _isCrouched,
                bool _cuacking = false, bool _hasArmor = false, bool _hasHelmet = false):
            motion(_motion),
            stateTransition(_stateTransition),
            flipping(_flipping),
            isLookingUp(_isLookingUp),
            typeOnHand(_typeOnHand),
            isCrouched(_isCrouched),
            cuacking(_cuacking),
            hasArmor(_hasArmor),
            hasHelmet(_hasHelmet) {}
};

struct InstantProjectileEventDto {
    TypeProjectile type;
    Vector2D origin;
    Vector2D end;

    InstantProjectileEventDto() = default;
    InstantProjectileEventDto(TypeProjectile type, const Vector2D& origin, const Vector2D& end):
            type(type), origin(origin), end(end) {}
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
    std::vector<CollectableID_t> collectableDespawns;
    std::vector<CollectableSpawnEventDto> collectableSpawns;

    Snapshot(bool gameOver, const std::unordered_map<PlayerID_t, PlayerEvent>& updates,
             const std::vector<InstantProjectileEventDto>& raycastsEvents):
            gameOver(gameOver),
            updates(updates),
            raycastsEvents(raycastsEvents),
            collectableDespawns(),
            collectableSpawns() {}

    Snapshot(bool gameOver, const std::unordered_map<PlayerID_t, PlayerEvent>& updates,
             const std::vector<InstantProjectileEventDto>& raycastsEvents,
             const std::vector<CollectableID_t>& collectableDespawns,
             const std::vector<CollectableSpawnEventDto>& collectableSpawns):
            gameOver(gameOver),
            updates(updates),
            raycastsEvents(raycastsEvents),
            collectableDespawns(collectableDespawns),
            collectableSpawns(collectableSpawns) {}

    Snapshot(bool gameOver, const std::unordered_map<PlayerID_t, PlayerEvent>& updates):
            gameOver(gameOver), updates(updates) {}
};

#endif
