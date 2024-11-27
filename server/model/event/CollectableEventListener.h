#ifndef COLLECTABLE_EVENT_LISTENER_H
#define COLLECTABLE_EVENT_LISTENER_H
#include <vector>

#include "data/snapshot.h"

class CollectableEventListener {
private:
    std::vector<CollectableID_t>& despawnEvents;
    std::vector<CollectableSpawnEventDto>& spawnEvents;

public:
    CollectableEventListener(std::vector<CollectableID_t>& despawnEvents,
                             std::vector<CollectableSpawnEventDto>& spawnEvents);
    void DespawnEvent(CollectableID_t idDespawned);
    void SpawnEvent(const CollectableSpawnEventDto& e);
};

#endif
