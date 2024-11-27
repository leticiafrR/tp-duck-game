#include "Collectables.h"

#include "common/Collision.h"

Collectables::Collectables(): listener(nullptr), unicID(0), collectablesWrapps() {}

void Collectables::ResgisterListener(CollectableEventListener* l) { listener = l; }

void Collectables::DespawnCollectable(CollectableID_t idDespawn) {
    collectablesWrapps.erase(idDespawn);
    listener->DespawnEvent(idDespawn);
}

void Collectables::SpawnCollectable(Collectable* obj, float* sourceTimer) {

    collectablesWrapps[unicID] = CollectableWrapper(obj, sourceTimer);
    listener->SpawnEvent(CollectableSpawnEventDto(unicID, obj->GetTransform().GetPos(),
                                                  obj->GetTypeCollectable()));
    unicID++;
}


Collectable* Collectables::PickCollectable(const Transform& collectorSpace,
                                           TypeCollectable& collectorType) {
    auto it = std::find_if(
            collectablesWrapps.begin(), collectablesWrapps.end(), [&collectorSpace](auto& pair) {
                return Collision::RectCollision(pair.second.GetTransform(), collectorSpace);
            });


    if (it != collectablesWrapps.end()) {
        (*it).second.BeCollected(collectorType);
        Collectable* obj = (*it).second.GetCollectable();
        DespawnCollectable((*it).first);
        return obj;
    }
    return nullptr;
}
