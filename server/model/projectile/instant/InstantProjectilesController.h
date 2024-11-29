#ifndef INSTANT_PROJECTILES_CONTROLLER_H
#define INSTANT_PROJECTILES_CONTROLLER_H
#include <unordered_map>
#include <vector>

#include "InstantProjectile.h"

class InstantProjectilesController {
private:
    std::vector<InstantProjectile*> instantProjectiles;
    InstantProjectileEventListener* instantProjectileListener;
    void ReapDead();

public:
    InstantProjectilesController();
    InstantProjectileEventListener* GetInstantProjectileListener();
    void RegisterListener(InstantProjectileEventListener* listener);
    void RelaseProjectile(InstantProjectile* projectile);
    void Update(const StaticMap& map, std::unordered_map<PlayerID_t, Duck*>& players);
    ~InstantProjectilesController();
};
#endif
