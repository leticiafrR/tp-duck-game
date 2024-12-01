#include "LaserRifle.h"

#include "server/model/Duck.h"
#include "server/model/projectile/instant/BounceInstantProjectile.h"

LaserRifle::LaserRifle(ProjectilesController& controller, const Transform& initialSpace,
                       const Config& conf):
        Weapon(controller, initialSpace, conf.getLaserRifleScope(), conf.getLaserRifleAmmo(),
               conf.getDamageMedium(), conf.getShortDispersion(), conf.getCooldownBasic(),
               TypeProjectile::LASER, conf.getLaserRifleInclination()) {}


void LaserRifle::BeCollected(TypeCollectable& collectorTypeRef) {
    collectorTypeRef = TypeCollectable::LASER_RIFLE;
}

void LaserRifle::Shoot(Duck* shooter) {
    BounceInstantProjectile* projectile = new BounceInstantProjectile(
            shooter->GetTransform().GetPos(), GetShootingDirection(shooter), scope, damage,
            typeProjectile, l);
    projectilesController.RelaseInstantProjectile(projectile);
}

bool LaserRifle::Use(Duck* shooter) {
    if (Weapon::Use(shooter)) {
        shooter->StartShooting();
        shooter->ApplyRecoil(10);
        return true;
    }
    return false;
}
TypeCollectable LaserRifle::GetTypeCollectable() { return TypeCollectable::LASER_RIFLE; }
