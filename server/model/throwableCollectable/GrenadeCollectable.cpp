#include "GrenadeCollectable.h"

#include "server/model/Duck.h"
#include "server/model/throwable/Grenade.h"

GrenadeCollectable::GrenadeCollectable(ProjectilesController& projectilesController,
                                       const Transform& initialSpace):
        ThrowableCollectable(initialSpace), projectilesController(projectilesController) {}

void GrenadeCollectable::BeCollected(TypeItem& typeOnHandRef) { typeOnHandRef = TypeItem::GRENADE; }

TypeItem GrenadeCollectable::GetTypeCollectable() { return TypeItem::GRENADE; }

bool GrenadeCollectable::Use(Duck* thrower) {
    thrower->PrepareToThrow(
            std::make_shared<Grenade>(projectilesController, TypeItem::GRENADE_UNLOCK),
            TypeItem::GRENADE_UNLOCK);
    return true;
}
