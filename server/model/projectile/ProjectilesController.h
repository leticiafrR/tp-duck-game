
#ifndef PROJECTILES_CONTROLLER_H
#define PROJECTILES_CONTROLLER_H
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "../event/InstantProjectileEventListener.h"
#include "../map/staticMap.h"
#include "common/Vector2D.h"
#include "instant/InstantProjectile.h"

class ProjectilesController {
private:
    std::vector<InstantProjectile*> instantProjectiles;
    // std::unordered_map<ProjectileID_t,ThrowableProjectile*> throwableProjectiles;
    InstantProjectileEventListener* instantProjectileListener;

public:
    ProjectilesController();

    InstantProjectileEventListener* GetInstantProjectileListener();

    void RegisterListener(InstantProjectileEventListener* listener);

    void RelaseInstantProjectile(InstantProjectile* projectile);

    void Update(const StaticMap& map, std::unordered_map<PlayerID_t, Duck*>& players);

    void ReapDead();

    ~ProjectilesController();
};

#endif
