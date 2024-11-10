#ifndef EVENTS_MANAGER_H
#define EVENTS_MANAGER_H
#include <iostream>
#include <unordered_map>
#include <vector>

#include "data/id.h"
#include "data/snapshot.h"

#include "PlayerEventListener.h"

class Duck;
class EventsManager {
private:
    std::unordered_map<PlayerID_t, PlayerEvent> events;
    std::vector<PlayerEventListener*> listeners;

public:
    void SendListeners(const std::unordered_map<PlayerID_t, Duck*>& players);
    Snapshot GetSnapshot(bool gameOver);
    ~EventsManager();
};

#endif
