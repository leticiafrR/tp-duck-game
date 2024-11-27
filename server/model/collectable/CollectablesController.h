#ifndef COLLECTABLES_CONTROLLER_H
#define COLLECTABLES_CONTROLLER_H

#include <algorithm>
#include <vector>

#include "Collectables.h"
#include "CollectablesSpawner.h"
class Transform;
class Collectable;
class CollectableEventListener;
class ProjectilesController;
class Config;

class CollectablesController {
private:
    Collectables collectables;
    CollectablesSpawner collectablesSnpawner;

public:
    explicit CollectablesController(ProjectilesController& projectilesController,
                                    const Config& conf, const std::vector<Vector2D>& positions);
    Collectable* TryCollect(const Transform& collectorSpace, TypeCollectable& collectorTyperRef);
    void Drop(Collectable* obj, const Vector2D& position);
    void RegisterListener(CollectableEventListener* collectableListener);
    void Update(float deltaTime);
};

#endif
