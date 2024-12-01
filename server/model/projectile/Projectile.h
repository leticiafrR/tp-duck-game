#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <unordered_map>
#include <utility>

#include "common/Vector2D.h"
#include "server/model/event/ProjectileEventListener.h"

enum TypeProjectile;
class Duck;
class StaticMap;


class Projectile {
protected:
    TypeProjectile type;
    bool isDead;
    Vector2D rayOrigin;
    Vector2D rayDirection;
    float rayLenght;
    uint8_t damage;
    ProjectileEventListener* l;

    void CheckCollisionWithMap(const StaticMap& map);
    void CheckCollisionWithDuck(Duck* duck);

public:
    Projectile(const Vector2D& shooterPos, const Vector2D& direction, float scope, uint8_t damage,
               TypeProjectile type, ProjectileEventListener* l);

    void RegistListener(ProjectileEventListener* listener);
    virtual void Update(const StaticMap& map, std::unordered_map<PlayerID_t, Duck*>& players);
    void MarkAsDead();
    bool IsDead();
    virtual ~Projectile() = default;
};

#endif
