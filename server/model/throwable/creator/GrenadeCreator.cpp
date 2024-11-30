#include "GrenadeCreator.h"

GrenadeCreator::GrenadeCreator(ProjectilesController& projectilesController,
                               const Transform& initialSpace):
        ThrowableCreator(initialSpace), projectilesController(projectilesController) {}

std::shared_ptr<Throwable> GrenadeCreator::GetThrowable() {
    return std::make_shared<Grenade>(projectilesController);
}

void GrenadeCreator::BeCollected(TypeCollectable& typeOnHandRef) {
    typeOnHandRef = TypeCollectable::GRENADE;
}

TypeCollectable GrenadeCreator::GetTypeCollectable() { return TypeCollectable::GRENADE; }
