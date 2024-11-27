#include "CollectablesController.h"

#include "server/config.h"
#include "server/model/event/CollectableEventListener.h"
#include "server/model/projectile/ProjectilesController.h"

CollectablesController::CollectablesController(ProjectilesController& projectilesController,
                                               const Config& conf,
                                               const std::vector<Vector2D>& positions):
        collectablesSpawner(positions, projectilesController, conf) {}

std::shared_ptr<Collectable> CollectablesController::TryCollect(const Transform& collectorSpace,
                                                                TypeCollectable& collectorType) {
    return collectables.PickCollectable(collectorSpace, collectorType);
}

void CollectablesController::Drop(std::shared_ptr<Collectable> obj, const Vector2D& position) {
    obj->BeDropped(position);
    collectables.SpawnCollectable(obj);
}

void CollectablesController::RegisterListener(CollectableEventListener* collectableListener) {
    collectables.ResgisterListener(collectableListener);
}

void CollectablesController::Update(float deltaTime) {
    collectablesSpawner.Update(deltaTime, collectables);
}
