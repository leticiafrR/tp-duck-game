#ifndef SHOTGUN_H
#define SHOTGUN_H
#include "../InstantWeapon.h"

#define AMMO_WITH_RELOAD(x) ((x)*2)

class Shotgun: public InstantWeapon {
private:
    /* sin disparo continuo, necesita recargar municiones */
    bool ammoLoaded;

public:
    Shotgun(ProjectilesController& controller, const Transform& initialSpace, const Config& conf):
            InstantWeapon(controller, initialSpace, conf.getShotgunScope(),
                          AMMO_WITH_RELOAD(conf.getShotgunAmmo()), conf.getDamageShort(),
                          conf.getLongDispersion(), conf.getCooldownBasic(),
                          TypeProjectile::FRAGMENT),
            ammoLoaded(true) {}


    void BeCollected(TypeCollectable& collectorTypeRef) override {
        collectorTypeRef = TypeCollectable::SHOTGUN;
    }

    void Shoot(Duck* shooter) override {
        if (ammoLoaded) {
            shooter->StartShooting();
            for (int i = 0; i < 6; i++) {
                InstantProjectile* projectile = new InstantProjectile(
                        shooter->GetTransform().GetPos(), GetShootingDirection(shooter), scope,
                        damage, typeProjectile, l);
                projectilesController.RelaseProjectile(projectile);
            }
            ammoLoaded = false;
        } else {
            ammoLoaded = true;
        }
    }
    ~Shotgun() = default;
};


#endif
