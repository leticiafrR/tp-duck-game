#ifndef INSTANT_PROJECTILE_H
#define INSTANT_PROJECTILE_H
#include <unordered_map>
#include <utility>

#include "../Duck.h"
#include "../event/InstantProjectileEventListener.h"
#include "../map/staticMap.h"
#include "common/Vector2D.h"
#include "data/snapshot.h"

#include "ReboundController.h"

enum TypeProjectile;
class InstantProjectile: public Projectile {
protected:
    Vector2D rayOrigin;
    Vector2D rayDirection;
    float rayLenght;
    uint8_t damage;
    InstantProjectileEventListener* l;

    void CheckCollisionWithMap(const StaticMap& map) {
        std::optional<std::pair<float, bool>> maybeInfoCollision =
                map.CheckCollisionRay(rayOrigin, rayDirection, rayLenght);
        if (maybeInfoCollision.has_value()) {
            rayLenght = maybeInfoCollision.value().first;
        }
    }

    void CheckCollisionWithDuck(Duck* duck) {
        if (Collision::Raycast(rayOrigin, rayDirection, rayLenght, duck->GetTransform())) {
            duck->HandleReceiveDamage(damage);
        }
    }

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

    virtual void Update(const StaticMap& map,
                        std::unordered_map<PlayerID_t, Duck*>& players) override {

        // virtual void Update(const StaticMap& map, std::unordered_map<PlayerID_t, Duck*>&
        // players,ReboundsController& reboundsController) override {
        CheckCollisionWithMap(map);
        for (const auto& pair: players) {
            CheckCollisionWithDuck(pair.second);
        }
        l->NewInstantProjectileEvent(type, rayOrigin, rayOrigin + rayDirection * rayLenght);
        MarkAsDead();
    }
};
#endif
