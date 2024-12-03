#include "Projectile.h"

#include "../Duck.h"
#include "data/snapshot.h"
#include "server/model/box/Box.h"
#include "server/model/map/staticMap.h"

Projectile::Projectile(const Vector2D& shooterPos, const Vector2D& direction, float scope,
                       uint8_t damage, TypeProjectile type, ProjectileEventListener* l,
                       uint8_t intensityExplotion):
        type(type),
        isDead(false),
        rayOrigin(shooterPos),
        rayDirection(direction),
        rayLenght(scope),
        damage(damage),
        intensityExplotion(intensityExplotion),
        l(l) {}

void Projectile::CheckCollisionWithMap(const StaticMap& map) {
    std::optional<std::pair<float, bool>> maybeInfoCollision =
            map.CheckCollisionRay(rayOrigin, rayDirection, rayLenght);
    if (maybeInfoCollision.has_value()) {
        rayLenght = maybeInfoCollision.value().first;
    }
}

void Projectile::CheckCollisionWithDuck(Duck* duck) {
    if (Collision::Raycast(rayOrigin, rayDirection, rayLenght, duck->GetTransform())) {
        duck->HandleReceiveDamage(damage, intensityExplotion);
    }
}

void Projectile::RegistListener(ProjectileEventListener* listener) { l = listener; }

void Projectile::CheckCollisionWithBoxes(std::unordered_map<BoxID_t, Box>& boxes) {
    for (auto pair: boxes) {
        if (Collision::Raycast(rayOrigin, rayDirection, rayLenght, pair.second.GetTransform())) {
            boxes[pair.first].ReceiveDamage(damage);
            std::cout << "UNA CAJA FUE LASTIMADA\n";
        }
    }
}

void Projectile::Update(const StaticMap& map, std::unordered_map<PlayerID_t, Duck*>& players,
                        std::unordered_map<BoxID_t, Box>& boxes) {
    CheckCollisionWithMap(map);
    CheckCollisionWithBoxes(boxes);
    for (const auto& pair: players) {
        CheckCollisionWithDuck(pair.second);
    }
    l->NewProjectileEvent(type, rayOrigin, rayOrigin + rayDirection * rayLenght);
    MarkAsDead();
}

void Projectile::MarkAsDead() { isDead = true; }
bool Projectile::IsDead() { return isDead; }
