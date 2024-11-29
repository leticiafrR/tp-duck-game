#include "InstantProjectile.h"

#include "../../Duck.h"
#include "data/snapshot.h"
#include "server/model/map/staticMap.h"

InstantProjectile::InstantProjectile(const Vector2D& shooterPos, const Vector2D& direction,
                                     float scope, uint8_t damage, TypeProjectile type,
                                     InstantProjectileEventListener* l):
        Projectile(type),
        rayOrigin(shooterPos),
        rayDirection(direction),
        rayLenght(scope),
        damage(damage),
        l(l) {}

void InstantProjectile::CheckCollisionWithMap(const StaticMap& map) {
    std::optional<std::pair<float, bool>> maybeInfoCollision =
            map.CheckCollisionRay(rayOrigin, rayDirection, rayLenght);
    if (maybeInfoCollision.has_value()) {
        rayLenght = maybeInfoCollision.value().first;
    }
}

void InstantProjectile::CheckCollisionWithDuck(Duck* duck) {
    if (Collision::Raycast(rayOrigin, rayDirection, rayLenght, duck->GetTransform())) {
        duck->HandleReceiveDamage(damage);
    }
}

void InstantProjectile::RegistListener(InstantProjectileEventListener* listener) { l = listener; }

void InstantProjectile::Update(const StaticMap& map,
                               std::unordered_map<PlayerID_t, Duck*>& players) {

    CheckCollisionWithMap(map);
    for (const auto& pair: players) {
        CheckCollisionWithDuck(pair.second);
    }
    l->NewInstantProjectileEvent(type, rayOrigin, rayOrigin + rayDirection * rayLenght);
    MarkAsDead();
}
