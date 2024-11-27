#include "InstantProjectileEventListener.h"
InstantProjectileEventListener::InstantProjectileEventListener(
        std::vector<InstantProjectileEventDto>& events):
        events(events) {}

void InstantProjectileEventListener::NewInstantProjectileEvent(TypeProjectile type,
                                                               const Vector2D& origin,
                                                               const Vector2D& end) {
    events.emplace_back(type, origin, end);
}
