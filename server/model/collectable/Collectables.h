#ifndef COLLECTABLES_H
#define COLLECTABLES_H
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
    void SpawnCollectable(Collectable* obj, float* sourceTimer);


    Collectable* PickCollectable(const Transform& collectorSpace, TypeCollectable& collectorType);
};
#endif
