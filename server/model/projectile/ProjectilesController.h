
#ifndef PROJECTILES_CONTROLLER_H
#define PROJECTILES_CONTROLLER_H
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "../event/InstantProjectileEventListener.h"
#include "../map/staticMap.h"
#include "common/Vector2D.h"

#include "Projectile.h"

class ProjectilesController {
private:
    std::vector<Projectile*> projectiles;
    InstantProjectileEventListener* instantProjectileListener;

public:
    ProjectilesController();

    InstantProjectileEventListener* GetInstantProjectileListener();

    void RegisterListener(InstantProjectileEventListener* listener);

    void RelaseProjectile(Projectile* projectile);

    void Update(const StaticMap& map, std::unordered_map<PlayerID_t, Duck*>& players);

    void ReapDead();

    ~ProjectilesController();
};

#endif
