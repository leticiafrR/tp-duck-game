#include "GrenadeCollectable.h"

GrenadeCollectable::GrenadeCollectable(ProjectilesController& projectilesController,
                                       const Transform& initialSpace):
        ThrowableCollectable(initialSpace), projectilesController(projectilesController) {}

std::shared_ptr<Throwable> GrenadeCollectable::GetThrowable() {
    return std::make_shared<Grenade>(projectilesController);
}

void GrenadeCollectable::BeCollected(TypeCollectable& typeOnHandRef) {
    typeOnHandRef = TypeCollectable::GRENADE;
}

TypeCollectable GrenadeCollectable::GetTypeCollectable() { return TypeCollectable::GRENADE; }
