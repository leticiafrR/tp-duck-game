#ifndef COLLECTABLE_SPAWNER_H
#define COLLECTABLE_SPAWNER_H
#include <ctime>
#include <random>

#include "common/Vector2D.h"

#include "includes.h"

class Collectables;
class CollectableSpawner {
private:
    const float timeToRespawn;
    float timer;
    const Transform spawnPlace;
    ProjectilesController& projectilesController;
    const Config& conf;

    TypeCollectable GetRandomTypeCollectable();
    Collectable* GetCollectable(TypeCollectable type);

public:
    CollectableSpawner(const Vector2D& pos, ProjectilesController& projectilesController,
                       const Config& conf);
    void Update(float deltaTime, Collectables& collectables);

    // CollectableSpawner(CollectableSpawner&&) = delete;
    // CollectableSpawner& operator=(CollectableSpawner&&) = delete;
};

#endif
