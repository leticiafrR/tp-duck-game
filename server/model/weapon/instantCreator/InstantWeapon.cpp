#include "InstantWeapon.h"

#include "server/model/Duck.h"
#include "server/model/projectile/instant/InstantProjectile.h"

InstantWeapon::InstantWeapon(ProjectilesController& projectilesController,
                             const Transform& initialSpace, float scope, uint16_t ammo,
                             uint8_t damage, float dispersionRange, float cooldown,
                             TypeProjectile typeProjectile, float inclination):
        Weapon(projectilesController, initialSpace, ammo),
        typeProjectile(typeProjectile),
        scope(scope),
        damage(damage),
        dispersionRange(dispersionRange),
        cooldown(cooldown),
        cooldownTimer(0),
        inclination(inclination),
        l(projectilesController.GetInstantProjectileListener()) {}

float InstantWeapon::RandomDisturbance() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> dist(-dispersionRange, dispersionRange);
    return dist(generator);
}

Vector2D InstantWeapon::GetShootingDirection(Duck* shooter) {
    Vector2D direction = shooter->GetLookVector();
    if (inclination && shooter->GetFlip() == Flip::Left) {
        direction.Rotate(-inclination);
    } else if (inclination) {
        direction.Rotate(inclination);
    }

    if (shooter->IsShooting() && dispersionRange != 0) {
        direction += (Vector2D::GetOrthogonal(direction)) * RandomDisturbance();
    }
    return direction.Normalized();
}

void InstantWeapon::Shoot(Duck* shooter) {
    InstantProjectile* projectile =
            new InstantProjectile(shooter->GetTransform().GetPos(), GetShootingDirection(shooter),
                                  scope, damage, typeProjectile, l);
    projectilesController.RelaseInstantProjectile(projectile);
}

bool InstantWeapon::Use(Duck* shooter) {
    if (ammo > 0 && cooldown <= cooldownTimer) {
        Shoot(shooter);
        ammo--;
        cooldownTimer = 0;
        return true;
    }
    return false;
}

void InstantWeapon::Update(float deltaTime) {
    if (cooldownTimer <= cooldown) {
        cooldownTimer += deltaTime;
    }
}
