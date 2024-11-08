#ifndef EVENTS_MANAGER_H
#define EVENTS_MANAGER_H
#include <unordered_map>
#include <vector>

#include "../Duck.h"

class EventsManager {
private:
    std::unordered_map<PlayerID_t, PlayerEvent> events;
    std::vector<PlayerEventListener*> listeners;

public:
    void SendListeners(const std::unordered_map<PlayerID_t, Duck*>& players);
    Snapshot GetSnapshot(bool gameOver);
    ~EventsManager();
};


/**********************************************************************************
 *                              DEFINITIONS
 ***********************************************************************************/

Snapshot EventsManager::GetSnapshot(bool gameOver) {
    Snapshot s(gameOver, events);
    events.clear();
    return s;
}

void EventsManager::SendListeners(const std::unordered_map<PlayerID_t, Duck*>& players) {
    for (const auto& pair: players) {
        Duck* player = pair.second;
        PlayerID_t id = pair.first;

        PlayerEventListener* l = new PlayerEventListener(events, id);
        listeners.push_back(l);
        player->RegistListener(l);
    }
}

EventsManager::~EventsManager() {
    for (PlayerEventListener* listener: listeners) {
        delete listener;
    }
    listeners.clear();
}

#endif
