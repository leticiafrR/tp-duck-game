#ifndef LASER_RIFLE_H
#define LASER_RIFLE_H
#include "InstantWeapon.h"

class LaserRifle: public InstantWeapon {
public:
    LaserRifle(ProjectilesController& controller, const Transform& initialSpace,
               const Config& conf);
    void BeCollected(TypeCollectable& collectorTypeRef) override;
    void Shoot(Duck* shooter) override;
    bool Use(Duck* shooter) override;
    TypeCollectable GetTypeCollectable() override;
};

#endif
