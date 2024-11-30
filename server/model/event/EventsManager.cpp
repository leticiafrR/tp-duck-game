#include "EventsManager.h"

#include "../Duck.h"
#include "../collectable/CollectablesController.h"
#include "../projectile/ProjectilesController.h"
#include "../throwable/ThrowablesController.h"
EventsManager::EventsManager():
        playerListener(playerEvents),
        instantProjectileListener(instantProjectileEvents),
        collectableListener(collectableDespawnEvents, collectableSpawnEvents),
        throwableListener(throwablesSpawnings, throwablesDespawnings) {}

Snapshot EventsManager::GetSnapshot(bool gameOver) {
    Snapshot s(gameOver, playerEvents, instantProjectileEvents, collectableDespawnEvents,
               collectableSpawnEvents, throwablesSpawnings, throwablesDespawnings);
    for (auto& pair: throwablesSpawnings) {
        std::cout << "[snapshot]: \n ->ID: " << (int)pair.first
                  << "\n  ->position: " << pair.second.position.ToString() << std::endl
                  << std::endl;
    }
    playerEvents.clear();
    instantProjectileEvents.clear();
    collectableDespawnEvents.clear();
    collectableSpawnEvents.clear();
    throwablesSpawnings.clear();
    throwablesDespawnings.clear();
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

void EventsManager::SendThrowableListener(ThrowablesController& throwablesController) {
    throwablesController.RegisterListener(&throwableListener);
}
