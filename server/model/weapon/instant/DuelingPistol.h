#ifndef DUELING_PISTOL_H
#define DUELING_PISTOL_H
#include "../InstantWeapon.h"
class DuelingPistol: public InstantWeapon {

public:
    DuelingPistol(ProjectilesController& controller, const Transform& initialSpace,
                  const Config& conf):
            InstantWeapon(controller, initialSpace, conf.getDuelingPistolScope(),
                          conf.getDuelingPistolAmmo(), conf.getDamageLong(),
                          conf.getSuperDispersion(), conf.getCooldownBasic(),
                          TypeProjectile::BULLET) {}


    void BeCollected(TypeCollectable& collectorTypeRef) override {
        collectorTypeRef = TypeCollectable::DUELING_PISTOL;
    }

    bool Use(Duck* shooter) override {
        shooter->StartShooting();
        return InstantWeapon::Use(shooter);
    }
};

#endif
