#ifndef DUELING_PISTOL_H
#define DUELING_PISTOL_H
#include "../InstantWeapon.h"
class DuelingPistol: public InstantWeapon {
public:
    DuelingPistol(ProjectilesController& controller, const Transform& initialSpace,
                  const Config& conf);
    void BeCollected(TypeCollectable& collectorTypeRef) override;
    bool Use(Duck* shooter) override;
    TypeCollectable GetTypeCollectable() override;
};

#endif
