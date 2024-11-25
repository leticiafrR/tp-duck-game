#ifndef LASER_RIFLE_H
#define LASER_RIFLE_H
#include "../InstantWeapon.h"
#include "server/model/projectile/BouncingInstantProjectile.h"
class LaserRifle: public InstantWeapon {

    // para esta arma es suficiente con la definiciòn estandart de de instantWeapon para generar
    // proyectiles

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
        BouncingInstantProjectile* projectile = new BouncingInstantProjectile(
                shooter->GetTransform().GetPos(), GetShootingDirection(shooter), scope, damage,
                typeProjectile, l);
        projectilesController.RelaseProjectile(projectile);
    }
    bool Use(Duck* shooter) override {
        // genera disparos continuos
        if (InstantWeapon::Use(shooter)) {
            shooter->StartShooting();
            shooter->ApplyRecoil(10);
            return true;
        }
        return false;
    }
};

#endif
