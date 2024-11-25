
#ifndef BOUNCING_INSTANT_PROJECTILE_H
#define BOUNCING_INSTANT_PROJECTILE_H
#include <cmath>
#include <optional>
#include <unordered_map>
#include <utility>

#include "InstantProjectile.h"

class BouncingInstantProjectile: public InstantProjectile {
private:
    // float

    std::optional<std::pair<float, Duck*>> CheckImpactWithSomeDuck(
            const std::unordered_map<PlayerID_t, Duck*>& players) {
        Duck* woundedDuck = nullptr;
        float distanceUntilImpact = INFINITY;
        for (const auto& pair: players) {
            Duck* candidate = pair.second;
            std::pair<float, bool> infoCollision = Collision::RaycastDistanceAndDirection(
                    rayOrigin, rayDirection, rayLenght, candidate->GetTransform());
            if (infoCollision.first < distanceUntilImpact && infoCollision.first < rayLenght) {
                distanceUntilImpact = infoCollision.first;
                woundedDuck = candidate;
            }
        }
        return ((woundedDuck) ?
                        std::nullopt :
                        std::optional<std::pair<float, Duck*>>({distanceUntilImpact, woundedDuck}));
    }

    void HandleCollisionWithMap(std::pair<float, bool> infoCollision) {
        // rebound
        float reboundLenght = rayLenght - (infoCollision.first);
        rayLenght = infoCollision.first;
        l->NewInstantProjectileEvent(type, rayOrigin, rayOrigin + rayDirection * rayLenght);
        std::cout << "ORIGEN: " << rayOrigin.ToString() << " LENGHT: " << rayLenght
                  << " DIRECTION: " << rayDirection.ToString() << std::endl;

        Vector2D reboundDirection = rayDirection.ReflectAcross(
                (infoCollision.second ? Vector2D::Right() : Vector2D::Up()));
        // Vector2D reboundDirection = rayDirection.ReflectAcross((infoCollision.second ?
        // Vector2D::Down() : Vector2D::Left()));
        std::cout << "DIRECCION DE REBOTE: " << reboundDirection.ToString() << std::endl;

        rayDirection = reboundDirection;
        rayOrigin = rayOrigin + rayDirection * rayLenght;
        rayLenght = reboundLenght;
        if (rayLenght <= 0) {
            MarkAsDead();
            std::cout << "deberia estar muerto\n";
        }
    }

    void HandleCollisionWithDuck(std::pair<float, Duck*> infoCollision) {
        // impact
        infoCollision.second->HandleReceiveDamage(damage);
        rayLenght = infoCollision.first;
        l->NewInstantProjectileEvent(type, rayOrigin, rayOrigin + rayDirection * rayLenght);
        MarkAsDead();
    }

    bool CheckCollision(const StaticMap& map,
                        const std::unordered_map<PlayerID_t, Duck*>& players) {
        std::optional<std::pair<float, Duck*>> maybeInfoCollisionWithDuck =
                CheckImpactWithSomeDuck(players);
        std::optional<std::pair<float, bool>> maybeInfoCollisionWithMap =
                map.CheckCollisionRay(rayOrigin, rayDirection, rayLenght);

        if (maybeInfoCollisionWithDuck.has_value() && maybeInfoCollisionWithMap.has_value()) {
            std::pair<float, Duck*> infoCollisionWithDuck = maybeInfoCollisionWithDuck.value();
            std::pair<float, bool> infoCollisionWithMap = maybeInfoCollisionWithMap.value();
            if (infoCollisionWithDuck.first < infoCollisionWithMap.first) {
                HandleCollisionWithDuck(infoCollisionWithDuck);
            } else {
                HandleCollisionWithMap(infoCollisionWithMap);
            }
        } else if (maybeInfoCollisionWithDuck.has_value()) {
            HandleCollisionWithDuck(maybeInfoCollisionWithDuck.value());
        } else if (maybeInfoCollisionWithMap.has_value()) {
            HandleCollisionWithMap(maybeInfoCollisionWithMap.value());
        } else {
            return false;
        }
        return true;
    }

public:
    BouncingInstantProjectile(const Vector2D& origin, const Vector2D& direction, float scope,
                              uint8_t damage, TypeProjectile type,
                              InstantProjectileEventListener* l):
            InstantProjectile(origin, direction, scope, damage, type, l) {}


    void Update(const StaticMap& map, std::unordered_map<PlayerID_t, Duck*>& players) override {
        // void Update(const StaticMap& map, std::unordered_map<PlayerID_t, Duck*>& players)
        // override {
        if ((rayLenght <= 0) || !CheckCollision(map, players)) {
            l->NewInstantProjectileEvent(type, rayOrigin, rayOrigin + rayDirection * rayLenght);
            MarkAsDead();
            if (rayLenght > 0) {
                std::cout << "se termina de recorrer sin collision\n";
            } else {
                std::cout << "hubo colisiòn\n";
            }
        }
    }
};


#endif
