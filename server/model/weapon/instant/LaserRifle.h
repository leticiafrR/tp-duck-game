#ifndef LASER_RIFLE_H
#define LASER_RIFLE_H
#include "../InstantWeapon.h"
class LaserRifle: public InstantWeapon {


    // para esta arma es suficiente con la definiciòn estandart de de instantWeapon para generar
    // proyectiles

public:
    LaserRifle(ProjectilesController& controller, const Transform& initialSpace,
               const Config& conf):
            InstantWeapon(controller, initialSpace, conf.getLaserRifleScope(),
                          conf.getLaserRifleAmmo(), conf.getDamageMedium(),
                          conf.getShortDispersion(), conf.getCooldownBasic(),
                          TypeProjectile::RayoLaser) {}


    void BeCollected(TypeCollectable& collectorTypeRef) override {
        collectorTypeRef = TypeCollectable::LASER_RIFLE;
    }

    bool Use(Duck* shooter) override {
        // genera disparos continuos
        if (InstantWeapon::Use(shooter)) {
            std::cout << "Entra\n";
            shooter->StartShooting();
            shooter->ApplyRecoil(30);  // era 5
            return true;
        }
        return false;
    }
};

#endif