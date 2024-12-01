#ifndef GRENADE_COLLECTABLE_H
#define GRENADE_COLLECTABLE_H
#include <memory>

#include "server/model/throwable/Grenade.h"

#include "ThrowableCollectable.h"
class GrenadeCollectable: public ThrowableCollectable {
    ProjectilesController& projectilesController;

public:
    GrenadeCollectable(ProjectilesController& projectilesController, const Transform& initialSpace);
    std::shared_ptr<Throwable> GetThrowable() override;
    void BeCollected(TypeCollectable& typeOnHandRef) override;
    TypeCollectable GetTypeCollectable() override;
    ~GrenadeCollectable() = default;
};


#endif
