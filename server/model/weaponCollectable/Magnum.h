#ifndef MAGNUM_H
#define MAGNUM_H
#include "Weapon.h"

class Magnum: public Weapon {
public:
    Magnum(ProjectilesController& controller, const Transform& initialSpace, const Config& conf);

    void BeCollected(TypeItem& typeOnHandRef) override;
    TypeItem GetTypeCollectable() override;
    bool Use(Duck* shooter) override;
};
#endif
