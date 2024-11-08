#ifndef PLAYER_EVENT_LISTENER_H
#define PLAYER_EVENT_LISTENER_H

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

/**********************************************************************************
 *                              DEFINITIONS
 ***********************************************************************************/

void PlayerEventListener::Motion() {
    PlayerEvent& e = events[sourceId];
    std::cout << "SE REGISTRÒ CAMBIO DE POSICIÒN\n";
    e.motion = motionEventSrc->GetPos();
    e.stateTransition = *stateEventSrc;
    e.flipping = *flippingEventSrc;
}

// la facing face cambia con la intenciòn del usuario(con donde te movès en realidad )
void PlayerEventListener::Flipping() {
    PlayerEvent& e = events[sourceId];
    std::cout << "SE REGISTRA FLIPPING\n";
    e.flipping = *flippingEventSrc;
    e.motion = motionEventSrc->GetPos();
    e.stateTransition = *stateEventSrc;
}

// por el momento solo se muere al caerse
void PlayerEventListener::StateTransition() {
    PlayerEvent& e = events[sourceId];
    std::cout << "SE REGISTRA CAMBIO DE ESTADO\n";
    e.stateTransition = *stateEventSrc;
    e.flipping = *flippingEventSrc;
    e.motion = motionEventSrc->GetPos();
}

PlayerEventListener::PlayerEventListener(std::unordered_map<PlayerID_t, PlayerEvent>& events,
                                         PlayerID_t sourceId):
        events(events),
        sourceId(sourceId),
        motionEventSrc(nullptr),
        flippingEventSrc(nullptr),
        stateEventSrc(nullptr) {}

void PlayerEventListener::Suscribe(Transform* motionEventSrc, Flip* flippingEventSrc,
                                   DuckState* stateEventSrc) {
    this->motionEventSrc = motionEventSrc;
    this->flippingEventSrc = flippingEventSrc;
    this->stateEventSrc = stateEventSrc;
}

#endif
