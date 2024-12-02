#ifndef INSTANT_WEAPON_H
#define INSTANT_WEAPON_H

#include <random>

#include "../collectable/Collectable.h"
#include "server/config.h"
#include "server/model/event/ProjectileEventListener.h"
#include "server/model/projectile/Projectile.h"
#include "server/model/projectile/ProjectilesController.h"

#define NO_INCLINATION 0

class Weapon: public Collectable {
protected:
    ProjectilesController& projectilesController;
    uint16_t ammo;
    TypeProjectile typeProjectile;
    const float scope;
    const uint8_t damage;
    float dispersionRange;
    const float cooldown;
    float cooldownTimer;
    float inclination;
    ProjectileEventListener* l;

    float RandomDisturbance();
    virtual void Shoot(Duck* shooter);
    virtual Vector2D GetShootingDirection(Duck* shooter);

public:
    Weapon(ProjectilesController& projectilesController, const Transform& initialSpace, float scope,
           uint16_t ammo, uint8_t damage, float dispersionRange, float cooldown,
           TypeProjectile typeProjectile, float inclination = NO_INCLINATION);

    virtual void BeCollected(TypeItem& typeOnHandRef) override = 0;
    virtual bool Use(Duck* shooter) override;
    void Update(float deltaTime) override;
    virtual ~Weapon() = default;
    virtual TypeItem GetTypeCollectable() override = 0;
    bool StillReusable() override;
    void StopUse(Duck* shooter) override;
};

#endif
