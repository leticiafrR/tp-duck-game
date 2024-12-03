#include "Weapon.h"

#include "server/model/Duck.h"
#include "server/model/projectile/Projectile.h"

Weapon::Weapon(ProjectilesController& projectilesController, const Transform& initialSpace,
               float scope, uint16_t ammo, uint8_t damage, float dispersionRange, float cooldown,
               TypeProjectile typeProjectile, float inclination):
        Collectable(initialSpace),
        projectilesController(projectilesController),
        ammo(ammo),
        typeProjectile(typeProjectile),
        scope(scope),
        damage(damage),
        dispersionRange(dispersionRange),
        cooldown(cooldown),
        cooldownTimer(0),
        inclination(inclination),
        l(projectilesController.GetInstantProjectileListener()) {}

float Weapon::RandomDisturbance() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> dist(-dispersionRange, dispersionRange);
    return dist(generator);
}

Vector2D Weapon::GetShootingDirection(Duck* shooter) {
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

void Weapon::Shoot(Duck* shooter) {
    Projectile* projectile =
            new Projectile(shooter->GetTransform().GetPos(), GetShootingDirection(shooter), scope,
                           damage, typeProjectile, l);
    projectilesController.RelaseProjectile(projectile);
}

bool Weapon::Use(Duck* shooter) {
    if (ammo > 0 && cooldown <= cooldownTimer) {
        Shoot(shooter);
        ammo--;
        cooldownTimer = 0;
        return true;
    }
    return false;
}

void Weapon::Update(float deltaTime) {
    if (cooldownTimer <= cooldown) {
        cooldownTimer += deltaTime;
    }
}


bool Weapon::StillReusable() { return ammo > 0; }

void Weapon::StopUse(Duck* shooter) { shooter->StopShooting(); }
