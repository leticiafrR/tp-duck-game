#ifndef THROWABLE_EVENT_LISTENER_H
#define THROWABLE_EVENT_LISTENER_H
#include <unordered_map>
#include <vector>

#include "data/snapshot.h"


class ThrowableEventListener {
private:
    std::unordered_map<ThrowableID_t, ThrowableSpawnEventDto>& spawnings;
    std::vector<ThrowableID_t>& despawnings;

public:
    ThrowableEventListener(std::unordered_map<ThrowableID_t, ThrowableSpawnEventDto>& spawnings,
                           std::vector<ThrowableID_t>& despawnings):
            spawnings(spawnings), despawnings(despawnings) {}

    void Moving(ThrowableID_t sourceID, ThrowableSpawnEventDto event) {
        std::cout << "moving Throwable with ID " << (int)sourceID << "\n";
        spawnings[sourceID] = event;
    }
    void Despawning(ThrowableID_t sourceID) { despawnings.push_back(sourceID); }
};


#endif
