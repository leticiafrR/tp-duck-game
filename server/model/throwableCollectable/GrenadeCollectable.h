#ifndef GRENADE_COLLECTABLE_H
#define GRENADE_COLLECTABLE_H
#include <memory>

#include "server/model/projectile/ProjectilesController.h"

#include "ThrowableCollectable.h"
class GrenadeCollectable: public ThrowableCollectable {
private:
    ProjectilesController& projectilesController;

public:
    GrenadeCollectable(ProjectilesController& projectilesController, const Transform& initialSpace);
    void BeCollected(TypeItem& typeOnHandRef) override;
    TypeItem GetTypeCollectable() override;
    bool Use(Duck* thrower) override;
    ~GrenadeCollectable() = default;
};


#endif
