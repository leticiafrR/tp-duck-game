#ifndef PLAYER_EVENT_LISTENER_H
#define PLAYER_EVENT_LISTENER_H

#include <unordered_map>

#include "common/Transform.h"
#include "data/snapshot.h"

class PlayerEventListener {
private:
    std::unordered_map<PlayerID_t, PlayerEvent>& events;

public:
    explicit PlayerEventListener(std::unordered_map<PlayerID_t, PlayerEvent>& events):
            events(events) {}

    void NewPlayerEvent(PlayerID_t sourceID, PlayerEvent event) { events[sourceID] = event; }
};

#endif
