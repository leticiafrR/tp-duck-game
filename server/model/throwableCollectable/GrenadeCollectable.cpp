#include "GrenadeCollectable.h"

#include "server/model/Duck.h"
#include "server/model/throwable/Grenade.h"

GrenadeCollectable::GrenadeCollectable(ProjectilesController& projectilesController,
                                       const Transform& initialSpace):
        ThrowableCollectable(initialSpace), projectilesController(projectilesController) {}

void GrenadeCollectable::BeCollected(TypeCollectable& typeOnHandRef) {
    typeOnHandRef = TypeCollectable::GRENADE;
}

TypeCollectable GrenadeCollectable::GetTypeCollectable() { return TypeCollectable::GRENADE; }
bool GrenadeCollectable::GrenadeCollectable::Use(Duck* thrower) {
    thrower->PrepareToThrow(
            std::make_shared<Grenade>(projectilesController, TypeCollectable::GRENADE_UNLOCK),
            TypeCollectable::GRENADE_UNLOCK);
    return true;
}
