#ifndef EVENTS_MANAGER_H
#define EVENTS_MANAGER_H
#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>
#include <vector>

#include "data/id.h"
#include "data/snapshot.h"

#include "InstantProjectileEventListener.h"
#include "PlayerEventListener.h"

class Duck;
class ProjectilesController;

class EventsManager {
private:
    std::unordered_map<PlayerID_t, PlayerEvent> playerEvents;
    std::list<PlayerEventListener> playersListeners;

    std::vector<InstantProjectileEventDto> instantProjectileEvents;
    InstantProjectileEventListener instantProjectileListener;

public:
    EventsManager();
    void SendPlayersListeners(const std::unordered_map<PlayerID_t, Duck*>& players);
    void SendInstantProjectileListener(ProjectilesController& projectilesController);
    Snapshot GetSnapshot(bool gameOver);

    EventsManager(const EventsManager&) = delete;
    EventsManager& operator=(const EventsManager&) = delete;
};

#endif
