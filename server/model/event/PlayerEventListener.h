#ifndef PLAYER_EVENT_LISTENER_H
#define PLAYER_EVENT_LISTENER_H

#include <iostream>
#include <unordered_map>

#include "../../../data/snapshot.h"
#include "common/Transform.h"

class PlayerEventListener {
private:
    std::unordered_map<PlayerID_t, PlayerEvent>& events;  // 3 posibles containers
    PlayerID_t sourceId;

    Transform* motionEventSrc;
    Flip* flippingEventSrc;
    DuckState* stateEventSrc;

public:
    explicit PlayerEventListener(std::unordered_map<PlayerID_t, PlayerEvent>& events,
                                 PlayerID_t sourceId);

    void Suscribe(Transform* motionEventSrc, Flip* flippingEventSrc, DuckState* stateEventSrc);

    void Motion();
    void Flipping();
    void StateTransition();
};

#endif
