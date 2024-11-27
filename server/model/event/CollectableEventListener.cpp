#include "CollectableEventListener.h"

CollectableEventListener::CollectableEventListener(
        std::vector<CollectableID_t>& despawnEvents,
        std::vector<CollectableSpawnEventDto>& spawnEvents):
        despawnEvents(despawnEvents), spawnEvents(spawnEvents) {}

void CollectableEventListener::DespawnEvent(CollectableID_t idDespawned) {
    despawnEvents.push_back(idDespawned);
    // std::cout << "[DespawnEvent] Desaparaciòn detectada del id "<< idDespawned<< std::endl;
}

void CollectableEventListener::SpawnEvent(const CollectableSpawnEventDto& e) {
    spawnEvents.push_back(e);
    // std::cout << "[spawnEvent] aparaciòn detectada del id "<< e.id<<std::endl;
}
