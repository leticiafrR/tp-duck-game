#include "PlayerEventListener.h"


/**********************************************************************************
 *                              DEFINITIONS
 ***********************************************************************************/

void MostrarEvento(const PlayerEvent& e) {
    std::string flipping = (e.flipping == Flip::Left) ? "Left" : "Right";
    std::string state = "Idle";
    if (e.stateTransition == DuckState::JUMPING) {
        state = "jumping";
    }
    if (e.stateTransition == DuckState::FALLING) {
        state = "falling";
    }
    if (e.stateTransition == DuckState::RUNNING) {
        state = "running";
    }
    std::cout << "---> POSITION: (" << e.motion.x << "," << e.motion.y << ")\n";
    std::cout << "---> FLIPPING: " << flipping << "\n";
    std::cout << "---> STATE: " << state << "\n";
}

void PlayerEventListener::Motion() {
    PlayerEvent& e = events[sourceId];
    e.motion = motionEventSrc->GetPos();
    e.stateTransition = *stateEventSrc;
    e.flipping = *flippingEventSrc;
    MostrarEvento(e);
}

// la facing face cambia con la intenciòn del usuario(con donde te movès en realidad )
void PlayerEventListener::Flipping() {
    PlayerEvent& e = events[sourceId];
    e.flipping = *flippingEventSrc;
    e.motion = motionEventSrc->GetPos();
    e.stateTransition = *stateEventSrc;
    MostrarEvento(e);
}

// por el momento solo se muere al caerse
void PlayerEventListener::StateTransition() {
    PlayerEvent& e = events[sourceId];
    e.stateTransition = *stateEventSrc;
    e.flipping = *flippingEventSrc;
    e.motion = motionEventSrc->GetPos();
    MostrarEvento(e);
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
