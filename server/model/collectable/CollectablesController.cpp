#include "CollectablesController.h"

#include <algorithm>

#include "server/config.h"
#include "server/model/event/CollectableEventListener.h"
#include "server/model/projectile/ProjectilesController.h"

CollectablesController::CollectablesController(ProjectilesController& projectilesController,
                                               const Config& conf,
                                               const std::vector<Vector2D>& positions) {
    std::transform(positions.begin(), positions.end(), std::back_inserter(spawners),
                   [&](const Vector2D& pos) {
                       return CollectableSpawner(pos, projectilesController, conf);
                   });
}


std::shared_ptr<Collectable> CollectablesController::TryCollect(const Transform& collectorSpace,
                                                                TypeItem& collectorType) {
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
    for (CollectableSpawner& spawner: spawners) {
        spawner.Update(deltaTime, collectables);
    }
}
