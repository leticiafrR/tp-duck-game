#include "InstantProjectileEventListener.h"

InstantProjectileEventListener::InstantProjectileEventListener(
        std::vector<InstantProjectileEventDto>& events):
        events(events) {}

void InstantProjectileEventListener::NewInstantProjectile(const InstantProjectileEventDto& event) {
    events.push_back(event);
}
