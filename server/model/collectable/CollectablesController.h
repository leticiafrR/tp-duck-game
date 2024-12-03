#ifndef COLLECTABLES_CONTROLLER_H
#define COLLECTABLES_CONTROLLER_H

#include <algorithm>
#include <memory>
#include <vector>

#include "spawning/CollectableSpawner.h"
#include "spawning/Collectables.h"

#include "CollectablesFactory.h"
class Transform;
class Collectable;
class CollectableEventListener;
class ProjectilesController;
class Config;

class CollectablesController {
private:
    Collectables collectables;
    std::vector<CollectableSpawner> spawners;

public:
    explicit CollectablesController(CollectablesFactory& collectablesFactory,
                                    const std::vector<Vector2D>& positions);
    std::shared_ptr<Collectable> TryCollect(const Transform& collectorSpace,
                                            TypeItem& collectorTyperRef);
    void AddCollectable(std::shared_ptr<Collectable> obj);
    void RegisterListener(CollectableEventListener* collectableListener);
    void Update(float deltaTime);
};

#endif
