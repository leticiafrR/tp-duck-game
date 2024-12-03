#ifndef COLLECTABLE_SPAWNER_H
#define COLLECTABLE_SPAWNER_H
#include <ctime>
#include <memory>
#include <random>

#include "common/Vector2D.h"
#include "server/model/collectable/CollectablesFactory.h"

#include "includesCollectables.h"

class Collectables;
class CollectableSpawner {
private:
    const float timeToRespawn;
    std::shared_ptr<float> timer;
    const Vector2D position;
    CollectablesFactory& factory;

public:
    CollectableSpawner(const Vector2D& pos, CollectablesFactory& collectablesFactory);
    void Update(float deltaTime, Collectables& collectables);
};

#endif
