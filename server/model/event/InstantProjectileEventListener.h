#ifndef INSTANT_PROJECTILE_EVENT_LISTENER_H
#define INSTANT_PROJECTILE_EVENT_LISTENER_H
#include <utility>
#include <vector>

#include "common/Vector2D.h"
#include "data/snapshot.h"

class InstantProjectileEventListener {
private:
    std::vector<InstantProjectileEventDto>& events;

public:
    explicit InstantProjectileEventListener(std::vector<InstantProjectileEventDto>& events);

    void NewInstantProjectile(const InstantProjectileEventDto& event);
};

#endif
