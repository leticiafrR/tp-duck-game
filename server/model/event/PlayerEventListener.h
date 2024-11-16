#ifndef PLAYER_EVENT_LISTENER_H
#define PLAYER_EVENT_LISTENER_H

#include <unordered_map>

#include "common/Transform.h"
#include "data/snapshot.h"

class PlayerEventListener {
private:
    std::unordered_map<PlayerID_t, PlayerEvent>& events;
    PlayerID_t sourceId;

    Transform* motionEventSrc;
    Flip* flippingEventSrc;
    DuckState* stateEventSrc;

public:
    explicit PlayerEventListener(std::unordered_map<PlayerID_t, PlayerEvent>& events,
                                 PlayerID_t sourceId);

    void Suscribe(Transform* motionEventSrc, Flip* flippingEventSrc, DuckState* stateEventSrc);

    void NewPlayerEvent();
};

#endif
