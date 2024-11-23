
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
    std::vector<Projectile*> rebound;

public:
    ProjectilesController(): instantProjectileListener(nullptr) {}

    InstantProjectileEventListener* GetInstantProjectileListener() {
        return instantProjectileListener;
    }

    void RegisterListener(InstantProjectileEventListener* listener) {
        instantProjectileListener = listener;
    }

    void RelaseProjectile(Projectile* projectile) { projectiles.push_back(projectile); }

    void Update(const StaticMap& map, std::unordered_map<PlayerID_t, Duck*>& players) {
        for (auto projectile: projectiles) {
            projectile->Update(map, players);
        }
        ReapDead();
    }

    void ReapDead() {
        auto deleter = std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile* p) {
            if (p->IsDead()) {
                delete p;
                return true;
            }
            return false;
        });
        projectiles.erase(deleter, projectiles.end());
    }

    ~ProjectilesController() {
        for (Projectile* p: projectiles) {
            delete p;
        }
        projectiles.clear();
    }
};

#endif
