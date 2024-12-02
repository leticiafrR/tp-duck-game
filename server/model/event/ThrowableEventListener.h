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
                           std::vector<ThrowableID_t>& despawnings);

    void Moving(ThrowableID_t sourceID, ThrowableSpawnEventDto event);
    void Despawning(ThrowableID_t sourceID);
};


#endif
