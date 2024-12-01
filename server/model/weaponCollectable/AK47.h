
#ifndef AK47_H
#define AK47_H
#include "Weapon.h"
class AK47: public Weapon {
private:
    float dispersionRate;
    const float maxDispersionRate;
    void IncraseDispersion();

public:
    AK47(ProjectilesController& controller, const Transform& initialSpace, const Config& conf);
    void BeCollected(TypeCollectable& collectorTypeRef) override;
    void Shoot(Duck* shooter) override;
    TypeCollectable GetTypeCollectable() override;
    void StopUse(Duck* shooter) override;
    bool Use(Duck* shooter) override;
    ~AK47() = default;
};

#endif
