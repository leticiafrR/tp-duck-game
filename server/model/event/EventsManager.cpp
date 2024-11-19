#include "EventsManager.h"

#include "../Duck.h"
#include "../projectile/ProjectilesController.h"

EventsManager::EventsManager():
        instantProjectileEvents(), instantProjectileListener(instantProjectileEvents) {}

Snapshot EventsManager::GetSnapshot(bool gameOver) {
    Snapshot s(gameOver, playerEvents, instantProjectileEvents);
    playerEvents.clear();
    instantProjectileEvents.clear();
    return s;
}

void EventsManager::SendInstantProjectileListener(ProjectilesController& projectilesController) {
    projectilesController.RegisterListener(&instantProjectileListener);
}

void EventsManager::SendPlayersListeners(const std::unordered_map<PlayerID_t, Duck*>& players) {
    for (const auto& pair: players) {
        Duck* player = pair.second;
        PlayerID_t id = pair.first;

        playersListeners.emplace_back(playerEvents, id);
        player->RegistListener(&playersListeners.back());
    }
}
