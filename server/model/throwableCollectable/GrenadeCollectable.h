#ifndef GRENADE_COLLECTABLE_H
#define GRENADE_COLLECTABLE_H
#include <memory>

#include "ThrowableCollectable.h"
class GrenadeCollectable: public ThrowableCollectable {
private:
    ProjectilesController& projectilesController;

public:
    GrenadeCollectable(ProjectilesController& projectilesController, const Transform& initialSpace);
    void BeCollected(TypeCollectable& typeOnHandRef) override;
    TypeCollectable GetTypeCollectable() override;
    bool Use(Duck* thrower) override;
    ~GrenadeCollectable() = default;
};


#endif
