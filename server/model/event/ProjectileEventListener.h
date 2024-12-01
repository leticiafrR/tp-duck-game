#ifndef PROJECTILE_EVENT_LISTENER_H
#define PROJECTILE_EVENT_LISTENER_H
#include <utility>
#include <vector>

#include "common/Vector2D.h"
#include "data/snapshot.h"

class ProjectileEventListener {
private:
    std::vector<ProjectileEventDto>& events;

public:
    explicit ProjectileEventListener(std::vector<ProjectileEventDto>& events);
    void NewProjectileEvent(TypeProjectile type, const Vector2D& origin, const Vector2D& end);
};

#endif
