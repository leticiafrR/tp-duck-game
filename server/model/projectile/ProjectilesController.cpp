#include "ProjectilesController.h"

ProjectilesController::ProjectilesController(): instantProjectileListener(nullptr) {}

InstantProjectileEventListener* ProjectilesController::GetInstantProjectileListener() {
    return instantProjectileListener;
}

void ProjectilesController::RegisterListener(InstantProjectileEventListener* listener) {
    instantProjectileListener = listener;
}

void ProjectilesController::RelaseInstantProjectile(InstantProjectile* projectile) {
    instantProjectiles.push_back(projectile);
}

void ProjectilesController::Update(const StaticMap& map,
                                   std::unordered_map<PlayerID_t, Duck*>& players) {
    for (auto projectile: instantProjectiles) {
        projectile->Update(map, players);
    }
    ReapDead();
}

void ProjectilesController::ReapDead() {
    auto deleter =
            std::remove_if(instantProjectiles.begin(), instantProjectiles.end(), [](Projectile* p) {
                if (p->IsDead()) {
                    delete p;
                    return true;
                }
                return false;
            });
    instantProjectiles.erase(deleter, instantProjectiles.end());
}

ProjectilesController::~ProjectilesController() {
    for (Projectile* p: instantProjectiles) {
        delete p;
    }
    instantProjectiles.clear();
}
