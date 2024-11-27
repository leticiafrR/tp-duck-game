#include "EventsManager.h"

#include "../Duck.h"
#include "../collectable/CollectablesController.h"
#include "../projectile/ProjectilesController.h"
EventsManager::EventsManager():
        playerListener(playerEvents),
        instantProjectileListener(instantProjectileEvents),
        collectableListener(collectableDespawnEvents, collectableSpawnEvents) {}

Snapshot EventsManager::GetSnapshot(bool gameOver) {
    Snapshot s(gameOver, playerEvents, instantProjectileEvents, collectableDespawnEvents,
               collectableSpawnEvents);
    if (collectableDespawnEvents.size() > 0 || collectableSpawnEvents.size() > 0) {
        std::cout << "confirmaciòn de que al pedir una snapshot hay algo en un container\n";
    }
    playerEvents.clear();
    instantProjectileEvents.clear();
    collectableDespawnEvents.clear();
    collectableSpawnEvents.clear();
    return s;
}

void EventsManager::SendInstantProjectileListener(ProjectilesController& projectilesController) {
    projectilesController.RegisterListener(&instantProjectileListener);
}

void EventsManager::SendCollectableListener(CollectablesController& collectableContoller) {
    collectableContoller.RegisterListener(&collectableListener);
}
void EventsManager::SendPlayersListeners(const std::unordered_map<PlayerID_t, Duck*>& players) {
    for (const auto& pair: players) {
        Duck* player = pair.second;
        player->RegistListener(&playerListener);
    }
}
