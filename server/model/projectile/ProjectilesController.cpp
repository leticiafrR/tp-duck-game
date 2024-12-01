
#include "ProjectilesController.h"

ProjectilesController::ProjectilesController(): instantProjectileListener(nullptr) {}

ProjectileEventListener* ProjectilesController::GetInstantProjectileListener() {
    return instantProjectileListener;
}

void ProjectilesController::RegisterListener(ProjectileEventListener* listener) {
    instantProjectileListener = listener;
}

void ProjectilesController::RelaseProjectile(Projectile* projectile) {
    projectiles.push_back(projectile);
}

void ProjectilesController::Update(const StaticMap& map,
                                   std::unordered_map<PlayerID_t, Duck*>& players) {
    for (auto projectile: projectiles) {
        projectile->Update(map, players);
    }
    ReapDead();
}

void ProjectilesController::ReapDead() {
    auto deleter = std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile* p) {
        if (p->IsDead()) {
            delete p;
            return true;
        }
        return false;
    });
    projectiles.erase(deleter, projectiles.end());
}

ProjectilesController::~ProjectilesController() {
    for (Projectile* p: projectiles) {
        delete p;
    }
    projectiles.clear();
}
