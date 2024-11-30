#ifndef GRENADE_CREATOR_H
#define GRENADE_CREATOR_H
#include <memory>

#include "server/model/throwable/Grenade.h"

#include "ThrowableCreator.h"

class GrenadeCreator: public ThrowableCreator {
public:
    GrenadeCreator(ProjectilesController& projectilesController, const Transform& initialSpace);
    std::shared_ptr<Throwable> GetThrowable() override;
    void BeCollected(TypeCollectable& typeOnHandRef) override;
    TypeCollectable GetTypeCollectable() override;
    ~GrenadeCreator() = default;
};


#endif
