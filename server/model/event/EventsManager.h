#ifndef EVENTS_MANAGER_H
#define EVENTS_MANAGER_H
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "data/id.h"
#include "data/snapshot.h"

#include "CollectableEventListener.h"
#include "InstantProjectileEventListener.h"
#include "PlayerEventListener.h"
#include "ThrowableEventListener.h"

class Duck;
class ProjectilesController;
class CollectablesController;
class ThrowablesController;

class EventsManager {
private:
    std::unordered_map<PlayerID_t, PlayerEvent> playerEvents;
    std::vector<InstantProjectileEventDto> instantProjectileEvents;
    std::vector<CollectableID_t> collectableDespawnEvents;
    std::vector<CollectableSpawnEventDto> collectableSpawnEvents;

    std::unordered_map<ThrowableID_t, ThrowableSpawnEventDto> throwablesSpawnings;
    std::vector<ThrowableID_t> throwablesDespawnings;


    PlayerEventListener playerListener;
    InstantProjectileEventListener instantProjectileListener;
    CollectableEventListener collectableListener;
    ThrowableEventListener throwableListener;

public:
    EventsManager();

    void SendPlayersListeners(const std::unordered_map<PlayerID_t, Duck*>& players);
    void SendInstantProjectileListener(ProjectilesController& projectilesController);
    void SendCollectableListener(CollectablesController& collectableContoller);
    void SendThrowableListener(ThrowablesController& throwablesController);

    Snapshot GetSnapshot(bool gameOver);


    EventsManager(const EventsManager&) = delete;
    EventsManager& operator=(const EventsManager&) = delete;

    EventsManager(EventsManager&&) = delete;
    EventsManager& operator=(EventsManager&&) = delete;
};

#endif
