#include "Grenade.h"

#define MASS_GRENADE 4
#define SCOPE_GRENADE 30
#define DAMAGE_GRENADE 6
Grenade::Grenade(ProjectilesController& projectilesController, TypeItem type, float timeToExplote):
        Throwable(MASS_GRENADE, type), projectiles(projectilesController), timer(timeToExplote) {}

void Grenade::Update(const StaticMap& map, float deltaTime) {
    Throwable::Update(map, deltaTime);
    timer -= deltaTime;
    if (timer <= 0) {
        Explote();
    }
}

void Grenade::Explote() {
    Vector2D dir = Vector2D::Right();
    for (int i = 0; i < 5; i++, dir.Rotate(360 / 5)) {
        Projectile* fragment = new Projectile(mySpace.GetPos(), dir, SCOPE_GRENADE, DAMAGE_GRENADE,
                                              TypeProjectile::FRAGMENT,
                                              projectiles.GetInstantProjectileListener());
        projectiles.RelaseProjectile(fragment);
    }
    MarkAsDead();
}

void Grenade::CheckCollisionWithDucks(std::unordered_map<PlayerID_t, Duck*>& /*ducks*/) {}
