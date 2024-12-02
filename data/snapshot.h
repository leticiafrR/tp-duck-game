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
// typeItem
enum class TypeItem : uint8_t {
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
    GRENADE,
    BANANA,
    __typesCount,
    EMPTY,
    BANANA_PEEL,
    GRENADE_UNLOCK
};

struct PlayerEvent {
    Vector2D motion;
    DuckState stateTransition;
    Flip flipping;
    bool isLookingUp;
    TypeItem typeOnHand;
    bool isCrouched;
    bool cuacking;
    bool hasArmor;
    bool hasHelmet;

    PlayerEvent() = default;

    PlayerEvent(const Vector2D& _motion, DuckState _stateTransition, Flip _flipping,
                bool _isLookingUp, TypeItem _typeOnHand, bool _isCrouched, bool _cuacking = false,
                bool _hasArmor = false, bool _hasHelmet = false):
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

struct ProjectileEventDto {
    TypeProjectile type;
    Vector2D origin;
    Vector2D end;

    ProjectileEventDto() = default;
    ProjectileEventDto(TypeProjectile type, const Vector2D& origin, const Vector2D& end):
            type(type), origin(origin), end(end) {}
};


struct CollectableSpawnEventDto {
    CollectableID_t id;
    Vector2D position;
    TypeItem type;

    CollectableSpawnEventDto(CollectableID_t _id, const Vector2D& _position, TypeItem _type):
            id(_id), position(_position), type(_type) {}
    CollectableSpawnEventDto() = default;
};

struct ThrowableSpawnEventDto {
    TypeItem type;  //    BANANA_PEEL or GRENADE_UNLOCK
    Vector2D position;
    ThrowableSpawnEventDto() = default;
    ThrowableSpawnEventDto(TypeItem type, const Vector2D& position):
            type(type), position(position) {}
};

struct Snapshot: public NetworkMsg {
    bool gameOver;
    std::unordered_map<PlayerID_t, PlayerEvent> updates;
    std::vector<ProjectileEventDto> raycastsEvents;
    std::vector<CollectableID_t> collectableDespawns;
    std::vector<CollectableSpawnEventDto> collectableSpawns;
    std::unordered_map<ThrowableID_t, ThrowableSpawnEventDto> throwableSpawns;
    std::vector<ThrowableID_t> throwableDespawns;
    std::vector<BoxID_t> boxesDespawns;


    Snapshot(bool gameOver, const std::unordered_map<PlayerID_t, PlayerEvent>& updates,
             const std::vector<ProjectileEventDto>& raycastsEvents,
             const std::vector<CollectableID_t>& collectableDespawns,
             const std::vector<CollectableSpawnEventDto>& collectableSpawns,
             const std::unordered_map<ThrowableID_t, ThrowableSpawnEventDto>& throwableSpawns,
             const std::vector<ThrowableID_t>& throwableDespawns):
            gameOver(gameOver),
            updates(updates),
            raycastsEvents(raycastsEvents),
            collectableDespawns(collectableDespawns),
            collectableSpawns(collectableSpawns),
            throwableSpawns(throwableSpawns),
            throwableDespawns(throwableDespawns),
            boxesDespawns() {}


    Snapshot(bool gameOver, const std::unordered_map<PlayerID_t, PlayerEvent>& updates,
             const std::vector<ProjectileEventDto>& raycastsEvents,
             const std::vector<CollectableID_t>& collectableDespawns,
             const std::vector<CollectableSpawnEventDto>& collectableSpawns,
             const std::unordered_map<ThrowableID_t, ThrowableSpawnEventDto>& throwableSpawns,
             const std::vector<ThrowableID_t>& throwableDespawns,
             const std::vector<BoxID_t>& boxesDespawns):
            gameOver(gameOver),
            updates(updates),
            raycastsEvents(raycastsEvents),
            collectableDespawns(collectableDespawns),
            collectableSpawns(collectableSpawns),
            throwableSpawns(throwableSpawns),
            throwableDespawns(throwableDespawns),
            boxesDespawns(boxesDespawns) {}

    Snapshot(bool gameOver, const std::unordered_map<PlayerID_t, PlayerEvent>& updates):
            gameOver(gameOver), updates(updates) {}
};

#endif
