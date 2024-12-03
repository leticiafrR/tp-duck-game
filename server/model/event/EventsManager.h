#ifndef EVENTS_MANAGER_H
#define EVENTS_MANAGER_H
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "data/id.h"
#include "data/snapshot.h"

#include "BoxEventListener.h"
#include "CollectableEventListener.h"
#include "PlayerEventListener.h"
#include "ProjectileEventListener.h"
#include "ThrowableEventListener.h"

class Duck;
class ProjectilesController;
class CollectablesController;
class ThrowablesController;
class BoxesController;

class EventsManager {
private:
    std::unordered_map<PlayerID_t, PlayerEvent> playerEvents;
    std::vector<ProjectileEventDto> projectileEvents;
    std::vector<CollectableID_t> collectableDespawnEvents;
    std::vector<CollectableSpawnEventDto> collectableSpawnEvents;

    std::unordered_map<ThrowableID_t, ThrowableSpawnEventDto> throwablesSpawnings;
    std::vector<ThrowableID_t> throwablesDespawnings;

    std::vector<BoxID_t> destroyedBoxes;


    PlayerEventListener playerListener;
    ProjectileEventListener projectileListener;
    CollectableEventListener collectableListener;
    ThrowableEventListener throwableListener;
    BoxEventListener boxListener;

public:
    EventsManager();

    void SendPlayersListeners(const std::unordered_map<PlayerID_t, Duck*>& players);
    void SendProjectileListener(ProjectilesController& projectilesController);
    void SendCollectableListener(CollectablesController& collectableContoller);
    void SendThrowableListener(ThrowablesController& throwablesController);
    void SendBoxesListener(BoxesController& boxesController);

    Snapshot GetSnapshot(bool gameOver);


    EventsManager(const EventsManager&) = delete;
    EventsManager& operator=(const EventsManager&) = delete;

    EventsManager(EventsManager&&) = delete;
    EventsManager& operator=(EventsManager&&) = delete;
};

#endif
