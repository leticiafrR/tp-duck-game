#include "InstantWeapon.h"


float InstantWeapon::RandomDisturbance() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> dist(-dispersionRange, dispersionRange);
    return dist(generator);
}

InstantProjectile* InstantWeapon::Shoot(Duck* shooter) {
    Vector2D direction = shooter->GetLookVector();

    if (shooter->IsShooting() && dispersionRange != 0) {
        direction += (Vector2D::GetOrthogonal(direction)) * RandomDisturbance();
    }
    return new InstantProjectile(shooter->GetTransform().GetPos(), direction, scope, damage,
                                 typeProjectile, l);
}

InstantWeapon::InstantWeapon(ProjectilesController& projectilesController,
                             const Transform& initialSpace, float scope, uint16_t ammo,
                             uint8_t damage, float dispersionRange, float cooldown,
                             TypeProjectile typeProjectile):
        Weapon(projectilesController, initialSpace, ammo, typeProjectile),
        scope(scope),
        damage(damage),
        dispersionRange(dispersionRange),
        cooldown(cooldown),
        cooldownTimer(0),
        l(projectilesController.GetInstantProjectileListener()) {}


void InstantWeapon::Use(Duck* shooter) {
    if (ammo > 0 && cooldown <= cooldownTimer) {
        InstantProjectile* projectile = Shoot(shooter);
        projectilesController.RelaseProjectile(projectile);
        ammo--;
        cooldownTimer = 0;
    }
}

void InstantWeapon::Update(float deltaTime) {
    if (cooldownTimer <= cooldown) {
        cooldownTimer += deltaTime;
    }
}
