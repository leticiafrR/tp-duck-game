#ifndef INSTANT_PROJECTILE_H
#include <unordered_map>
#include <utility>

#include "../Projectile.h"
#include "common/Vector2D.h"
#include "server/model/event/InstantProjectileEventListener.h"

enum TypeProjectile;
class Duck;
class StaticMap;

class InstantProjectile: public Projectile {
protected:
    Vector2D rayOrigin;
    Vector2D rayDirection;
    float rayLenght;
    uint8_t damage;
    InstantProjectileEventListener* l;

    void CheckCollisionWithMap(const StaticMap& map);
    void CheckCollisionWithDuck(Duck* duck);

public:
    InstantProjectile(const Vector2D& shooterPos, const Vector2D& direction, float scope,
                      uint8_t damage, TypeProjectile type, InstantProjectileEventListener* l);

    void RegistListener(InstantProjectileEventListener* listener);
    virtual void Update(const StaticMap& map,
                        std::unordered_map<PlayerID_t, Duck*>& players) override;
};
#endif
