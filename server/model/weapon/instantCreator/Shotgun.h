#ifndef SHOTGUN_H
#define SHOTGUN_H
#include "InstantWeapon.h"

#define AMMO_WITH_RELOAD(x) ((x)*2)

class Shotgun: public InstantWeapon {
private:
    /* sin disparo continuo, necesita recargar municiones */
    bool ammoLoaded;

public:
    Shotgun(ProjectilesController& controller, const Transform& initialSpace, const Config& conf);
    void BeCollected(TypeCollectable& collectorTypeRef) override;
    void Shoot(Duck* shooter) override;
    TypeCollectable GetTypeCollectable() override;
    ~Shotgun() = default;
};


#endif
