#ifndef SNAPSHOT_DTA_H
#define SNAPSHOT_DTA_H
#include <string>
#include <unordered_map>
#include <vector>

#include "common/Vector2D.h"

#include "id.h"
#include "networkMsg.h"

enum class Flip : uint8_t { Left = 1, Right, Up };
enum class TypeProjectile : uint8_t { RayoLaser, Bullet, Banana, GranadaFragment };
enum class DuckState : uint8_t { IDLE = 1, JUMPING, FALLING, RUNNING, WOUNDED, DEAD };

struct PlayerEvent {
    Vector2D motion;
    DuckState stateTransition;
    Flip flipping;
};

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

struct MatchDto {
    PlayerID_t id;
    std::string creatorName;
    uint8_t currentPlayers;
    uint8_t maxPlayers;

    MatchDto(PlayerID_t creatorID, const std::string& _creatorName, uint8_t _currentPlayers,
             uint8_t _maxPlayers):
            id(creatorID),
            creatorName(_creatorName),
            currentPlayers(_currentPlayers),
            maxPlayers(_maxPlayers) {}
};

struct AvailableMatches: public NetworkMsg {
    std::vector<MatchDto> matches;
    explicit AvailableMatches(const std::vector<ActiveMatch>& _matches): matches(_matches) {}
};

#endif
