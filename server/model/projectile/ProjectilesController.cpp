
#include "ProjectilesController.h"

#include "../physicsConstants.h"

ProjectilesController::ProjectilesController(): instantProjectileListener(nullptr) {}

void ProjectilesController::Update(const StaticMap& map,
                                   std::unordered_map<PlayerID_t, Duck*>& players,
                                   std::unordered_map<BoxID_t, Box>& boxes) {
    for (auto projectile: projectiles) {
        projectile->Update(map, players, boxes);
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

void ProjectilesController::RelaseExplotion(const Vector2D& origin, int cantFragments) {
    if (cantFragments > 0) {
        Vector2D dir = Vector2D::Right();
        for (int i = 0; i < cantFragments; i++, dir.Rotate(FULL_SPIN / cantFragments)) {
            Projectile* fragment = new Projectile(origin, dir, SCOPE_EXPLOTION, DAMAGE_EXPLOTION,
                                                  TypeProjectile::FRAGMENT,
                                                  instantProjectileListener, INTENSITY_EXPLOTION);
            RelaseProjectile(fragment);
        }
    }
}

ProjectileEventListener* ProjectilesController::GetInstantProjectileListener() {
    return instantProjectileListener;
}

void ProjectilesController::RegisterListener(ProjectileEventListener* listener) {
    instantProjectileListener = listener;
}

void ProjectilesController::RelaseProjectile(Projectile* projectile) {
    projectiles.push_back(projectile);
}

ProjectilesController::~ProjectilesController() {
    for (Projectile* p: projectiles) {
        delete p;
    }
    projectiles.clear();
}
