#ifndef COLLECTABLES_H
#define COLLECTABLES_H
#include <memory>
#include <unordered_map>

#include "server/model/event/CollectableEventListener.h"

#include "CollectableWrapper.h"

class Collectables {
private:
    CollectableEventListener* listener;
    CollectableID_t unicID;
    std::unordered_map<CollectableID_t, CollectableWrapper> collectablesWrapps;

public:
    Collectables();
    void ResgisterListener(CollectableEventListener* l);

    void DespawnCollectable(CollectableID_t idDespawn);
    void SpawnCollectable(Collectable* obj,
                          std::shared_ptr<float> sourceTimer = std::shared_ptr<float>());


    Collectable* PickCollectable(const Transform& collectorSpace, TypeCollectable& collectorType);
};
#endif
