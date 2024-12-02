#include "ThrowableEventListener.h"
ThrowableEventListener::ThrowableEventListener(
        std::unordered_map<ThrowableID_t, ThrowableSpawnEventDto>& spawnings,
        std::vector<ThrowableID_t>& despawnings):
        spawnings(spawnings), despawnings(despawnings) {}

void ThrowableEventListener::Moving(ThrowableID_t sourceID, ThrowableSpawnEventDto event) {
    spawnings[sourceID] = event;
}
void ThrowableEventListener::Despawning(ThrowableID_t sourceID) { despawnings.push_back(sourceID); }
