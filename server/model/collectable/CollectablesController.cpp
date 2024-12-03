#include "CollectablesController.h"

#include <algorithm>

#include "server/config.h"
#include "server/model/event/CollectableEventListener.h"
#include "server/model/projectile/ProjectilesController.h"

CollectablesController::CollectablesController(CollectablesFactory& collectablesFactory,
                                               const std::vector<Vector2D>& positions) {

    std::transform(
            positions.begin(), positions.end(), std::back_inserter(spawners),
            [&](const Vector2D& pos) { return CollectableSpawner(pos, collectablesFactory); });
}


std::shared_ptr<Collectable> CollectablesController::TryCollect(const Transform& collectorSpace,
                                                                TypeItem& collectorType) {
    return collectables.PickCollectable(collectorSpace, collectorType);
}

void CollectablesController::AddCollectable(std::shared_ptr<Collectable> obj) {
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
