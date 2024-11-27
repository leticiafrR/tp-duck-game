#include "CollectablesSpawner.h"

#include "Collectables.h"

CollectablesSpawner::CollectablesSpawner(std::vector<Vector2D> positions,
                                         ProjectilesController& projectilesController,
                                         const Config& conf) {
    for (auto& pos: positions) {
        CollectableSpawner spawner(pos, projectilesController, conf);
        spawners.push_back(spawner);
    }
}

void CollectablesSpawner::Update(float deltaTime, Collectables& collectables) {
    for (CollectableSpawner& spawner: spawners) {
        spawner.Update(deltaTime, collectables);
    }
}
