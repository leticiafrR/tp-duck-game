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
    // cppcheck-suppress unusedStructMember
    DuckState stateTransition;
    // cppcheck-suppress unusedStructMember
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

struct ActiveMatch {  // si o si manejarlo en un map para considerar el ID
    // cppcheck-suppress unusedStructMember
    PlayerID_t id;
    std::string name;  // considero necesario para que el usuario pueda ver el nombre de la match
    // cppcheck-suppress unusedStructMember
    uint8_t actualPlayers;
    // cppcheck-suppress unusedStructMember
    uint8_t maxPlayers;
    ActiveMatch(const PlayerID_t& _id, const std::string& _name, uint8_t _actualPlayers,
                uint8_t _maxPlayers):
            id(_id), name(_name), actualPlayers(_actualPlayers), maxPlayers(_maxPlayers) {}
};

struct ListActiveMatches: public NetworkMsg {
    std::unordered_map<PlayerID_t, ActiveMatch> matches;
    explicit ListActiveMatches(const std::unordered_map<PlayerID_t, ActiveMatch>& _matches):
            matches(_matches) {}
};
#endif
