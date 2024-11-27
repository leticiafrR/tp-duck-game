#ifndef LASER_RIFLE_H
#define LASER_RIFLE_H
#include "../InstantWeapon.h"
#include "server/model/projectile/BounceInstantProjectile.h"
class LaserRifle: public InstantWeapon {
public:
    LaserRifle(ProjectilesController& controller, const Transform& initialSpace,
               const Config& conf):
            InstantWeapon(controller, initialSpace, conf.getLaserRifleScope(),
                          conf.getLaserRifleAmmo(), conf.getDamageMedium(),
                          conf.getShortDispersion(), conf.getCooldownBasic(), TypeProjectile::LASER,
                          conf.getLaserRifleInclination()) {}


    void BeCollected(TypeCollectable& collectorTypeRef) override {
        collectorTypeRef = TypeCollectable::LASER_RIFLE;
    }

    void Shoot(Duck* shooter) override {
        BounceInstantProjectile* projectile = new BounceInstantProjectile(
                shooter->GetTransform().GetPos(), GetShootingDirection(shooter), scope, damage,
                typeProjectile, l);
        projectilesController.RelaseProjectile(projectile);
    }

    bool Use(Duck* shooter) override {
        if (InstantWeapon::Use(shooter)) {
            shooter->StartShooting();
            shooter->ApplyRecoil(10);
            return true;
        }
        return false;
    }
    TypeCollectable GetTypeCollectable() override { return TypeCollectable::LASER_RIFLE; }
};

#endif
