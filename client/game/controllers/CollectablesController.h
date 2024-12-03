#ifndef COLLECTABLES_CONTROLLER_H
#define COLLECTABLES_CONTROLLER_H
#include <unordered_map>

#include "../items/Collectable.h"
#include "client/Framework.h"

using std::unordered_map;

class CollectablesController {
private:
    ResourceManager& resourceManager;
    unordered_map<CollectableID_t, Collectable> collectables;

public:
    explicit CollectablesController(ResourceManager& resourceManager);
    ~CollectablesController();

    void SpawnCollectable(CollectableSpawnEventDto collectableData);
    void DespawnCollectable(CollectableID_t id);

    void Draw(Camera& cam);
};

#endif
