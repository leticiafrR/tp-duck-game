#include "CollectableEventListener.h"

CollectableEventListener::CollectableEventListener(
        std::vector<CollectableID_t>& despawnEvents,
        std::vector<CollectableSpawnEventDto>& spawnEvents):
        despawnEvents(despawnEvents), spawnEvents(spawnEvents) {}

void CollectableEventListener::DespawnEvent(CollectableID_t idDespawned) {
    despawnEvents.push_back(idDespawned);
}

void CollectableEventListener::SpawnEvent(const CollectableSpawnEventDto& e) {
    spawnEvents.push_back(e);
}
