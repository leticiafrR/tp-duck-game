#include "ProjectileEventListener.h"
ProjectileEventListener::ProjectileEventListener(std::vector<ProjectileEventDto>& events):
        events(events) {}

void ProjectileEventListener::NewProjectileEvent(TypeProjectile type, const Vector2D& origin,
                                                 const Vector2D& end) {
    events.emplace_back(type, origin, end);
}
