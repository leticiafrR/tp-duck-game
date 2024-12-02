#ifndef COLLECTABLE_SPAWNER_H
#define COLLECTABLE_SPAWNER_H
#include <ctime>
#include <memory>
#include <random>

#include "common/Vector2D.h"

#include "includesCollectables.h"

class Collectables;
class CollectableSpawner {
private:
    const float timeToRespawn;
    std::shared_ptr<float> timer;
    const Transform spawnPlace;
    ProjectilesController& projectilesController;
    const Config& conf;

    TypeItem GetRandomTypeCollectable();
    std::shared_ptr<Collectable> GetCollectable(TypeItem type);

public:
    CollectableSpawner(const Vector2D& pos, ProjectilesController& projectilesController,
                       const Config& conf);
    void Update(float deltaTime, Collectables& collectables);
};

#endif
