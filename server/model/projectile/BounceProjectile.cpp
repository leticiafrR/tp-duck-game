#include "BounceProjectile.h"

#include "../Duck.h"
#include "common/Collision.h"
#include "server/model/map/staticMap.h"

BounceProjectile::BounceProjectile(const Vector2D& origin, const Vector2D& direction, float scope,
                                   uint8_t damage, TypeProjectile type, ProjectileEventListener* l):
        Projectile(origin, direction, scope, damage, type, l) {}


std::optional<std::pair<float, Duck*>> BounceProjectile::CheckImpactWithSomeDuck(
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

    return ((!woundedDuck) ?
                    std::nullopt :
                    std::optional<std::pair<float, Duck*>>({distanceUntilImpact, woundedDuck}));
}

void BounceProjectile::HandleCollisionWithMap(std::pair<float, bool> infoCollision) {
    Vector2D rayEnd = rayOrigin + rayDirection * (infoCollision.first);
    l->NewProjectileEvent(type, rayOrigin, rayEnd);
    rayLenght = rayLenght - (rayEnd - rayOrigin).GetMagnitude();
    rayOrigin = rayEnd;
    rayDirection =
            rayDirection.ReflectAcross((infoCollision.second ? Vector2D::Right() : Vector2D::Up()));
    if (rayLenght <= 0) {
        MarkAsDead();
    }
}

void BounceProjectile::HandleCollisionWithDuck(std::pair<float, Duck*> infoCollision) {
    infoCollision.second->HandleReceiveDamage(damage);
    rayLenght = infoCollision.first;
    l->NewProjectileEvent(type, rayOrigin, rayOrigin + rayDirection * rayLenght);
    MarkAsDead();
}

bool BounceProjectile::CheckCollision(const StaticMap& map,
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

void BounceProjectile::Update(const StaticMap& map, std::unordered_map<PlayerID_t, Duck*>& players,
                              std::unordered_map<BoxID_t, Box>& /*boxes*/) {
    if (!CheckCollision(map, players)) {
        l->NewProjectileEvent(type, rayOrigin, rayOrigin + rayDirection * rayLenght);
        MarkAsDead();
    }
}
