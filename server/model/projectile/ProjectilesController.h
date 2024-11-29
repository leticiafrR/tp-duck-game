
#ifndef PROJECTILES_CONTROLLER_H
#define PROJECTILES_CONTROLLER_H

#include <iostream>
#include <unordered_map>
// #include "throwable/ThrowableProjectile.h"
#include "instant/InstantProjectilesController.h"
class StaticMap;
class Duck;


class ProjectilesController {
private:
    InstantProjectilesController instantProjectiles;
    // ThrowableProjectileID_t unicThrowableID;
    // std::unordered_map<ThrowableProjectileID_t,ThrowableProjectile*> throwableProjectiles;
public:
    // ProjectilesController();
    InstantProjectileEventListener* GetInstantProjectileListener();
    void RegisterListener(InstantProjectileEventListener* listener);
    void RelaseInstantProjectile(InstantProjectile* projectile);
    // void RelaseThrowableProjectile(ThrowableProjectile* projectile);
    void Update(const StaticMap& map, std::unordered_map<PlayerID_t, Duck*>& players,
                float deltaTime);
};

#endif
