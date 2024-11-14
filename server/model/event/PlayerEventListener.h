#ifndef PLAYER_EVENT_LISTENER_H
#define PLAYER_EVENT_LISTENER_H

#include <unordered_map>

#include "common/Transform.h"
#include "data/snapshot.h"

class PlayerEventListener {
private:
    // cppcheck-suppress unusedStructMember
    std::unordered_map<PlayerID_t, PlayerEvent>& events;
    PlayerID_t sourceId;
    // cppcheck-suppress unusedStructMember
    Transform* motionEventSrc;
    // cppcheck-suppress unusedStructMember
    Flip* flippingEventSrc;
    // cppcheck-suppress unusedStructMember
    DuckState* stateEventSrc;

public:
    explicit PlayerEventListener(std::unordered_map<PlayerID_t, PlayerEvent>& events,
                                 PlayerID_t sourceId);

    void Suscribe(Transform* motionEventSrc, Flip* flippingEventSrc, DuckState* stateEventSrc);

    void Motion();
    void Flipping();
    void StateTransition();
    void Wounded();
};

#endif
