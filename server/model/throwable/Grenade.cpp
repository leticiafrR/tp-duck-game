#include "Grenade.h"

#define MASS_GRENADE 4
#define TIME_TO_EXPLOTE 4  // parametrizable
#define SCOPE_GRENADE 30
#define DAMAGE_GRENADE 6
Grenade::Grenade(ProjectilesController& projectilesController):
        Throwable(MASS_GRENADE), projectiles(projectilesController), timer(TIME_TO_EXPLOTE) {}

TypeCollectable Grenade::GetTypeCollectable() { return TypeCollectable::GRENADE; }

void Grenade::Update(const StaticMap& map, float deltaTime) {
    Throwable::Update(map, deltaTime);
    timer -= deltaTime;
    if (timer <= 0) {
        Explote();
    } else if (throwingID != NOT_THROWED) {
        listener->Moving(throwingID, GetMovingEventDto());
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
    if (throwingID != NOT_THROWED) {
        listener->Despawning(throwingID);
    }
    MarkAsDead();
}

void Grenade::CheckCollisionWithDucks(std::unordered_map<PlayerID_t, Duck*>& /*ducks*/) {}
