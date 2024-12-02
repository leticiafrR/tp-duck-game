#ifndef SHOTGUN_H
#define SHOTGUN_H
#include "Weapon.h"

#define AMMO_WITH_RELOAD(x) ((x)*2)

class Shotgun: public Weapon {
private:
    /* sin disparo continuo, necesita recargar municiones */
    bool ammoLoaded;

public:
    Shotgun(ProjectilesController& controller, const Transform& initialSpace, const Config& conf);
    void BeCollected(TypeItem& collectorTypeRef) override;
    void Shoot(Duck* shooter) override;
    TypeItem GetTypeCollectable() override;
    ~Shotgun() = default;
};


#endif
