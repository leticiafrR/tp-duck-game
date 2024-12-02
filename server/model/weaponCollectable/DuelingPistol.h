#ifndef DUELING_PISTOL_H
#define DUELING_PISTOL_H
#include "Weapon.h"
class DuelingPistol: public Weapon {
public:
    DuelingPistol(ProjectilesController& controller, const Transform& initialSpace,
                  const Config& conf);
    void BeCollected(TypeItem& collectorTypeRef) override;
    bool Use(Duck* shooter) override;
    TypeItem GetTypeCollectable() override;
};

#endif
