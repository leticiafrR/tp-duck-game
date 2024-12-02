#include "EventsManager.h"

#include "../Duck.h"
#include "../collectable/CollectablesController.h"
#include "../projectile/ProjectilesController.h"
#include "../throwable/ThrowablesController.h"
EventsManager::EventsManager():
        playerListener(playerEvents),
        projectileListener(projectileEvents),
        collectableListener(collectableDespawnEvents, collectableSpawnEvents),
        throwableListener(throwablesSpawnings, throwablesDespawnings) {}

Snapshot EventsManager::GetSnapshot(bool gameOver) {
    Snapshot s(gameOver, playerEvents, projectileEvents, collectableDespawnEvents,
               collectableSpawnEvents, throwablesSpawnings, throwablesDespawnings);

    playerEvents.clear();
    projectileEvents.clear();
    collectableDespawnEvents.clear();
    collectableSpawnEvents.clear();
    throwablesSpawnings.clear();
    throwablesDespawnings.clear();
    return s;
}

void EventsManager::SendProjectileListener(ProjectilesController& projectilesController) {
    projectilesController.RegisterListener(&projectileListener);
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
