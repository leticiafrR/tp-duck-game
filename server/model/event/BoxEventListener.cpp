#include "BoxEventListener.h"

BoxEventListener::BoxEventListener(std::vector<BoxID_t>& despawns): despawns(despawns) {}

void BoxEventListener::DespawnBox(BoxID_t idDestroyed) { despawns.push_back(idDestroyed); }
