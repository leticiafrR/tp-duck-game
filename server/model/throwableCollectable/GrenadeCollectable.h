#ifndef GRENADE_COLLECTABLE_H
#define GRENADE_COLLECTABLE_H

#include "server/model/projectile/ProjectilesController.h"

#include "ThrowableCollectable.h"
class Config;
class GrenadeCollectable: public ThrowableCollectable {
private:
    ProjectilesController& projectilesController;
    int timeToExplote;

public:
    GrenadeCollectable(ProjectilesController& projectilesController, const Transform& initialSpace,
                       const Config& conf);
    void BeCollected(TypeItem& typeOnHandRef) override;
    TypeItem GetTypeCollectable() override;
    bool Use(Duck* thrower) override;
    ~GrenadeCollectable() = default;
};


#endif
