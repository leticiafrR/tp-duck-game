#ifndef COLLECTABLES_SPAWNER_H
#define COLLECTABLES_SPAWNER_H
#include <vector>

#include "common/Vector2D.h"

#include "CollectableSpawner.h"

class Collectables;
class CollectablesSpawner {
private:
    std::vector<CollectableSpawner> spawners;

public:
    CollectablesSpawner(std::vector<Vector2D> positions,
                        ProjectilesController& projectilesController, const Config& conf);
    void Update(float deltaTime, Collectables& collectables);
};


#endif
