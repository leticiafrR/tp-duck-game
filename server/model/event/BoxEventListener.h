#ifndef BOX_EVENT_LISTENER_H
#define BOX_EVENT_LISTENER_H
#include <vector>

#include "data/id.h"
class BoxEventListener {
private:
    std::vector<BoxID_t>& despawns;

public:
    explicit BoxEventListener(std::vector<BoxID_t>& despawns);
    void DespawnBox(BoxID_t idDestroyed);
};


#endif
