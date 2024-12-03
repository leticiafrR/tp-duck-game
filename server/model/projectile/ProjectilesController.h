#ifndef PROJECTILES_CONTROLLER_H
#define PROJECTILES_CONTROLLER_H
#include <unordered_map>
#include <vector>

#include "Projectile.h"

class ProjectilesController {
private:
    std::vector<Projectile*> projectiles;
    ProjectileEventListener* instantProjectileListener;
    void ReapDead();

public:
    ProjectilesController();
    ProjectileEventListener* GetInstantProjectileListener();
    void RegisterListener(ProjectileEventListener* listener);
    void RelaseProjectile(Projectile* projectile);
    void Update(const StaticMap& map, std::unordered_map<PlayerID_t, Duck*>& players,
                std::unordered_map<BoxID_t, Box>& boxes);
    ~ProjectilesController();
};
#endif
