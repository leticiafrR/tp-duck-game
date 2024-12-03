#include "Grenade.h"

#include "../physicsConstants.h"

#define MASS_GRENADE 4

Grenade::Grenade(ProjectilesController& projectilesController, TypeItem type, float timeToExplote):
        Throwable(MASS_GRENADE, type), projectiles(projectilesController), timer(timeToExplote) {}

void Grenade::Update(const StaticMap& map, float deltaTime) {
    Throwable::Update(map, deltaTime);
    timer -= deltaTime;
    if (timer <= 0) {
        projectiles.RelaseExplotion(mySpace.GetPos(), 5);
        MarkAsDead();
    }
}


void Grenade::CheckCollisionWithDucks(std::unordered_map<PlayerID_t, Duck*>& /*ducks*/) {}
