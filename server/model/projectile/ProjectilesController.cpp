#include "ProjectilesController.h"

InstantProjectileEventListener* ProjectilesController::GetInstantProjectileListener() {
    return instantProjectiles.GetInstantProjectileListener();
}
void ProjectilesController::RegisterListener(InstantProjectileEventListener* listener) {
    instantProjectiles.RegisterListener(listener);
}
void ProjectilesController::RelaseInstantProjectile(InstantProjectile* projectile) {
    instantProjectiles.RelaseProjectile(projectile);
}

void ProjectilesController::Update(const StaticMap& map,
                                   std::unordered_map<PlayerID_t, Duck*>& players,
                                   float deltaTime) {
    instantProjectiles.Update(map, players);
    if (deltaTime == 0) {
        std::cout << "holi\n";
    }
    // los throwables usan el delta
}


// ProjectilesController::ProjectilesController(): unicThrowableID(0){}

// void ProjectilesController::RelaseThrowableProjectile(ThrowableProjectile* projectile){
//     throwableProjectiles[unicThrowableID] = projectile;
//     unicThrowableID++;
// }

// void ProjectilesController::Update(const StaticMap& map,
//                                    std::unordered_map<PlayerID_t, Duck*>& players,float
//                                    deltaTime) {
//     for (auto projectile: instantProjectiles) {
//         projectile->Update(map, players);
//     }
//     for (auto& pair :throwableProjectiles ){
//         pair.second->Update(map,deltaTime);
//     }

//     ReapDead();
// }
