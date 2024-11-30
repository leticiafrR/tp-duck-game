#ifndef GRENADE_H
#define GRENADE_H
#include "server/model/projectile/ProjectilesController.h"

#include "Throwable.h"
#define MASS_GRENADE 2
#define TIME_TO_EXPLOTE 4  // parametrizable
#define SCOPE_GRENADE 30
#define DAMAGE_GRENADE 6

class Grenade: public Throwable {
private:
    ProjectilesController& projectiles;
    float timer;

public:
    explicit Grenade(ProjectilesController& projectilesController):
            Throwable(MASS_GRENADE), projectiles(projectilesController), timer(TIME_TO_EXPLOTE) {}

    void Update(const StaticMap& map, float deltaTime) override {
        Throwable::Update(map, deltaTime);
        timer -= deltaTime;
        if (timer <= 0) {
            Vector2D dir = Vector2D::Right();
            for (int i = 0; i < 5; i++, dir.Rotate(360 / 5)) {
                InstantProjectile* fragment = new InstantProjectile(
                        mySpace.GetPos(), dir, SCOPE_GRENADE, DAMAGE_GRENADE,
                        TypeProjectile::BULLET, projectiles.GetInstantProjectileListener());
                projectiles.RelaseInstantProjectile(fragment);
            }
            MarkAsDead();
        }
    }
    ~Grenade() = default;
    TypeCollectable GetTypeCollectable() override { return TypeCollectable::GRENADE; }
};


#endif
