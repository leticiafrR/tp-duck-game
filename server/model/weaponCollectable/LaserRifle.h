#ifndef LASER_RIFLE_H
#define LASER_RIFLE_H
#include "Weapon.h"

class LaserRifle: public Weapon {
public:
    LaserRifle(ProjectilesController& controller, const Transform& initialSpace,
               const Config& conf);
    void BeCollected(TypeItem& collectorTypeRef) override;
    void Shoot(Duck* shooter) override;
    bool Use(Duck* shooter) override;
    TypeItem GetTypeCollectable() override;
};

#endif
