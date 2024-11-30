#ifndef PEW_PEW_LASER_H
#define PEW_PEW_LASER_H
#include "InstantWeapon.h"
class PewPewLaser: public InstantWeapon {
public:
    PewPewLaser(ProjectilesController& controller, const Transform& initialSpace,
                const Config& conf);

    void BeCollected(TypeCollectable& collectorTypeRef) override;
    void Shoot(Duck* shooter) override;
    TypeCollectable GetTypeCollectable() override;
};

#endif
