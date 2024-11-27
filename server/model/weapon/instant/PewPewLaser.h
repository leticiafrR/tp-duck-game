#ifndef PEW_PEW_LASER_H
#define PEW_PEW_LASER_H
#include "../InstantWeapon.h"
class PewPewLaser: public InstantWeapon {
    /*sin disparos continuos, rafaga de 3, algo de dispersiòn*/
public:
    PewPewLaser(ProjectilesController& controller, const Transform& initialSpace,
                const Config& conf):
            InstantWeapon(controller, initialSpace, conf.getPewPewLaserScope(),
                          conf.getPewPewLaserAmmo(), conf.getDamageShort(), conf.getNoDispersion(),
                          conf.getCooldownBasic(), TypeProjectile::LASER,
                          conf.getHiperDispersion()) {}


    void BeCollected(TypeCollectable& collectorTypeRef) override {
        collectorTypeRef = TypeCollectable::PEW_PEW_LASER;
        std::cout << "[pewpew] recogiste una pewpew GRRRR\n";
    }

    void Shoot(Duck* shooter) override {
        float originalInclination = inclination;
        for (int i = -1; i < 2; i++) {
            InstantProjectile* projectile = new InstantProjectile(shooter->GetTransform().GetPos(),
                                                                  GetShootingDirection(shooter),
                                                                  scope, damage, typeProjectile, l);
            projectilesController.RelaseProjectile(projectile);
            inclination *= i;
        }
        inclination = originalInclination;
    }
    TypeCollectable GetTypeCollectable() override { return TypeCollectable::PEW_PEW_LASER; }
};


#endif
