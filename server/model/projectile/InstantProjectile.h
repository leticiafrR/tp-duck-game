#ifndef INSTANT_PROJECTILE_H
#define INSTANT_PROJECTILE_H
#include <unordered_map>

#include "../Duck.h"
#include "../event/InstantProjectileEventListener.h"
#include "../map/staticMap.h"
#include "common/Vector2D.h"
#include "data/snapshot.h"

#include "Projectile.h"

enum TypeProjectile;
class InstantProjectile: public Projectile {
private:
    Vector2D rayOrigin;
    Vector2D rayDirection;
    float rayLenght;
    uint8_t damage;
    InstantProjectileEventListener* l;

public:
    InstantProjectile(const Vector2D& shooterPos, const Vector2D& direction, float scope,
                      uint8_t damage, TypeProjectile type, InstantProjectileEventListener* l):
            Projectile(type),
            rayOrigin(shooterPos),
            rayDirection(direction),
            rayLenght(scope),
            damage(damage),
            l(l) {}

    void RegistListener(InstantProjectileEventListener* listener) { l = listener; }

    void CheckCollisionWithDuck(Duck* duck) {
        if (Collision::Raycast(rayOrigin, rayDirection, rayLenght, duck->GetTransform())) {
            duck->HandleReceiveDamage(damage);
        }
    }

    void UpdateLenght(const StaticMap& map) {
        std::optional<float> maybeNewLenght =
                map.CheckCollisionRay(rayOrigin, rayDirection, rayLenght);
        if (maybeNewLenght.has_value()) {
            rayLenght = maybeNewLenght.value();
        }
    }

    void Update(const StaticMap& map, std::unordered_map<PlayerID_t, Duck*>& players) override {
        UpdateLenght(map);
        for (const auto& pair: players) {
            CheckCollisionWithDuck(pair.second);
        }
        l->NewInstantProjectileEvent(type, rayOrigin, rayOrigin + rayDirection * rayLenght);
        MarkAsDead();
    }
};
#endif
