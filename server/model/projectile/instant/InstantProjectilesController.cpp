
#include "InstantProjectilesController.h"

InstantProjectilesController::InstantProjectilesController(): instantProjectileListener(nullptr) {}

InstantProjectileEventListener* InstantProjectilesController::GetInstantProjectileListener() {
    return instantProjectileListener;
}

void InstantProjectilesController::RegisterListener(InstantProjectileEventListener* listener) {
    instantProjectileListener = listener;
}

void InstantProjectilesController::RelaseProjectile(InstantProjectile* projectile) {
    instantProjectiles.push_back(projectile);
}

void InstantProjectilesController::Update(const StaticMap& map,
                                          std::unordered_map<PlayerID_t, Duck*>& players) {
    for (auto projectile: instantProjectiles) {
        projectile->Update(map, players);
    }
    ReapDead();
}

void InstantProjectilesController::ReapDead() {
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

InstantProjectilesController::~InstantProjectilesController() {
    for (Projectile* p: instantProjectiles) {
        delete p;
    }
    instantProjectiles.clear();
}
