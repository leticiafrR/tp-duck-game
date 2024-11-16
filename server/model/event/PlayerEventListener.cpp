#include "PlayerEventListener.h"

void PlayerEventListener::NewPlayerEvent() {
    PlayerEvent& e = events[sourceId];
    e.motion = motionEventSrc->GetPos();
    e.stateTransition = *stateEventSrc;
    e.flipping = *flippingEventSrc;
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
