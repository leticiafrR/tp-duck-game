#include "EventsManager.h"

#include "../Duck.h"
#include "../projectile/ProjectilesController.h"
/**********************************************************************************
 *                              DEFINITIONS
 ***********************************************************************************/
EventsManager::EventsManager():
        instantProjectileEvents(),
        instantProjectileListener(new InstantProjectileEventListener(instantProjectileEvents)) {}

Snapshot EventsManager::GetSnapshot(bool gameOver) {
    Snapshot s(gameOver, playerEvents, instantProjectileEvents);
    playerEvents.clear();
    instantProjectileEvents.clear();
    return s;
}

void EventsManager::SendInstantProjectileListener(ProjectilesController& projectilesController) {
    projectilesController.RegisterListener(instantProjectileListener);
}

void EventsManager::SendPlayersListeners(const std::unordered_map<PlayerID_t, Duck*>& players) {
    for (const auto& pair: players) {
        Duck* player = pair.second;
        PlayerID_t id = pair.first;

        PlayerEventListener* l = new PlayerEventListener(playerEvents, id);
        playersListeners.push_back(l);
        player->RegistListener(l);
    }
}

EventsManager::~EventsManager() {
    for (PlayerEventListener* listener: playersListeners) {
        delete listener;
    }
    playersListeners.clear();
    delete instantProjectileListener;
}
