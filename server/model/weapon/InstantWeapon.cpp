#include "InstantWeapon.h"


float InstantWeapon::RandomDisturbance() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> dist(-dispersionRange, dispersionRange);
    return dist(generator);
}

InstantProjectile* InstantWeapon::Shoot(Duck* shooter) {
    Vector2D direction = shooter->GetLookVector();
    if (inclination != 0) {
        if (shooter->GetFlip() == Flip::Left) {
            direction.Rotate(-inclination);
        } else {
            direction.Rotate(inclination);
        }
    }
    if (shooter->IsShooting() && dispersionRange != 0) {
        direction += (Vector2D::GetOrthogonal(direction)) * RandomDisturbance();
    }
    return new InstantProjectile(shooter->GetTransform().GetPos(), direction.Normalized(), scope,
                                 damage, typeProjectile, l);
}

InstantWeapon::InstantWeapon(ProjectilesController& projectilesController,
                             const Transform& initialSpace, float scope, uint16_t ammo,
                             uint8_t damage, float dispersionRange, float cooldown,
                             TypeProjectile typeProjectile, float inclination,
                             uint8_t projectilesPerShot):
        Weapon(projectilesController, initialSpace, ammo, typeProjectile),
        scope(scope),
        damage(damage),
        dispersionRange(dispersionRange),
        cooldown(cooldown),
        cooldownTimer(0),
        projectilesPerShot(projectilesPerShot),
        inclination(inclination),
        l(projectilesController.GetInstantProjectileListener()) {}


void InstantWeapon::Use(Duck* shooter) {
    if (ammo > 0 && cooldown <= cooldownTimer) {
        for (int i = 0; i < projectilesPerShot; i++) {
            InstantProjectile* projectile =
                    Shoot(shooter);  // la logica de disparar debe dejar la inclinaciòn preparada
                                     // para el siguiente disparo
            projectilesController.RelaseProjectile(projectile);
        }
        ammo--;
        cooldownTimer = 0;
    }
}

void InstantWeapon::Update(float deltaTime) {
    if (cooldownTimer <= cooldown) {
        cooldownTimer += deltaTime;
    }
}
