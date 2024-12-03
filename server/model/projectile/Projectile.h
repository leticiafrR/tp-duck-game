#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

#include "common/Vector2D.h"
#include "data/id.h"
#include "data/snapshot.h"
#include "server/model/event/ProjectileEventListener.h"


enum TypeProjectile;
class Duck;
class StaticMap;
class Box;
class Projectile {
protected:
    TypeProjectile type;
    bool isDead;
    Vector2D rayOrigin;
    Vector2D rayDirection;
    float rayLenght;
    uint8_t damage;
    uint8_t intensityExplotion;
    ProjectileEventListener* l;

    void CheckCollisionWithMap(const StaticMap& map);
    void CheckCollisionWithDuck(Duck* duck);
    void CheckCollisionWithBoxes(std::unordered_map<BoxID_t, Box>& boxes);

public:
    Projectile(const Vector2D& shooterPos, const Vector2D& direction, float scope, uint8_t damage,
               TypeProjectile type, ProjectileEventListener* l, uint8_t intensityExplotion = 0);

    void RegistListener(ProjectileEventListener* listener);
    virtual void Update(const StaticMap& map, std::unordered_map<PlayerID_t, Duck*>& players,
                        std::unordered_map<BoxID_t, Box>& boxes);
    void MarkAsDead();
    bool IsDead();
    virtual ~Projectile() = default;
};

#endif
