#include "PlayerEventListener.h"
PlayerEventListener::PlayerEventListener(std::unordered_map<PlayerID_t, PlayerEvent>& events):
        events(events) {}

void PlayerEventListener::NewPlayerEvent(PlayerID_t sourceID, PlayerEvent event) {
    events[sourceID] = event;
}
