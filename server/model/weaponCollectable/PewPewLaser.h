#ifndef PEW_PEW_LASER_H
#define PEW_PEW_LASER_H
#include "Weapon.h"
class PewPewLaser: public Weapon {
public:
    PewPewLaser(ProjectilesController& controller, const Transform& initialSpace,
                const Config& conf);

    void BeCollected(TypeItem& collectorTypeRef) override;
    void Shoot(Duck* shooter) override;
    TypeItem GetTypeCollectable() override;
};

#endif
