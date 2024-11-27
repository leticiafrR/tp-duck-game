#ifndef INSTANT_PROJECTILE_H
#define INSTANT_PROJECTILE_H
#include <string>
#include <unordered_map>
#include <utility>

#include "../event/InstantProjectileEventListener.h"
#include "../map/staticMap.h"
#include "common/Vector2D.h"

#include "Projectile.h"

enum TypeProjectile;
class Duck;

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
