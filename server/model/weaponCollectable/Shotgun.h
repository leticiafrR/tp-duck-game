#ifndef SHOTGUN_H
#define SHOTGUN_H
#include "Weapon.h"

class Shotgun: public Weapon {
private:
    bool ammoLoaded;

public:
    Shotgun(ProjectilesController& controller, const Transform& initialSpace, const Config& conf);
    void BeCollected(TypeItem& collectorTypeRef) override;
    void Shoot(Duck* shooter) override;
    TypeItem GetTypeCollectable() override;
    ~Shotgun() = default;
};


#endif
