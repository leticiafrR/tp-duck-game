#ifndef INSTANT_PROJECTILE_H
#define INSTANT_PROJECTILE_H
#include <unordered_map>

#include "../event/InstantProjectileEventListener.h"
#include "../map/staticMap.h"
#include "common/Vector2D.h"
#include "data/snapshot.h"

#include "Projectile.h"

// void ShowMyDto(){
//     std::cout << "[InstantProjectile] my Origin: ("<<rayOrigin.x<<","<<rayOrigin.y<<")\n";
//     std::cout << "[InstantProjectile] my direction:
//     ("<<rayDirection.x<<","<<rayDirection.y<<")\n"; std::cout << "[InstantProjectile] my lengh:
//     "<< rayLenght<<std::endl; std::cout << "[InstantProjectile] my damage: "<<(int) damage
//     <<std::endl;
// }

enum TypeProjectile;
class InstantProjectile: public Projectile {
private:
    Vector2D rayOrigin;
    Vector2D rayDirection;
    float rayLenght;
    uint8_t damage;
    InstantProjectileEventListener* l;

public:
    InstantProjectile(const Vector2D& shooterPos, const Flip& shooterFlip, float scope,
                      uint8_t damage, TypeProjectile type, InstantProjectileEventListener* l):
            Projectile(type),
            rayOrigin(shooterPos),
            rayDirection((shooterFlip == Flip::Left) ? Vector2D::Left() : Vector2D::Right()),
            rayLenght(scope),
            damage(damage),
            l(l) {}

    void RegistListener(InstantProjectileEventListener* listener) { l = listener; }

    void CheckCollisionWithDuck(Duck* duck) {
        std::cout << "[instantProjectile] CheckCollisionWithDuck\n";
        if (Collision::Raycast(rayOrigin, rayDirection, rayLenght, duck->GetTransform())) {
            duck->HandleReceiveDamage(damage);
        }
    }

    void UpdateLenght(const StaticMap& map) {
        std::optional<float> maybeNewLenght =
                map.CheckCollisionLateralRay(rayOrigin, rayDirection, rayLenght);
        if (maybeNewLenght.has_value()) {
            rayLenght = maybeNewLenght.value();
        }
    }

    void Update(const StaticMap& map, std::unordered_map<PlayerID_t, Duck*>& players) override {
        std::cout << "[instantProjectile] updating\n";
        UpdateLenght(map);
        for (auto& pair: players) {
            CheckCollisionWithDuck(pair.second);
        }
        std::cout << "[instantProjectile] notifying listener\n";
        l->NewInstantProjectile(type, rayOrigin, rayOrigin + rayDirection * rayLenght);
        std::cout << "[instantProjectile] marking as dead\n";
        MarkAsDead();  // al finalizar un tick, se elimina
    }

    void UpdateListener() {}
};
#endif
