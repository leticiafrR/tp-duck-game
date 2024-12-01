#include "LaserRifle.h"

#include "server/model/Duck.h"
#include "server/model/projectile/BounceProjectile.h"

LaserRifle::LaserRifle(ProjectilesController& controller, const Transform& initialSpace,
                       const Config& conf):
        Weapon(controller, initialSpace, conf.getLaserRifleScope(), conf.getLaserRifleAmmo(),
               conf.getDamageMedium(), conf.getShortDispersion(), conf.getCooldownBasic(),
               TypeProjectile::LASER, conf.getLaserRifleInclination()) {}


void LaserRifle::BeCollected(TypeCollectable& collectorTypeRef) {
    collectorTypeRef = TypeCollectable::LASER_RIFLE;
}

void LaserRifle::Shoot(Duck* shooter) {
    BounceProjectile* projectile =
            new BounceProjectile(shooter->GetTransform().GetPos(), GetShootingDirection(shooter),
                                 scope, damage, typeProjectile, l);
    projectilesController.RelaseProjectile(projectile);
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
