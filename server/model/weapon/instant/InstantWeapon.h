#ifndef INSTANT_WEAPON_H
#define INSTANT_WEAPON_H

#include <random>

#include "../Weapon.h"
#include "server/config.h"
#include "server/model/types.h"

class InstantWeapon: public Weapon {
protected:
    const float scope;
    const uint8_t damage;
    float dispersionRange;
    const float cooldown;
    float cooldownTimer;
    float inclination;
    InstantProjectileEventListener* l;

    float RandomDisturbance();
    virtual void Shoot(Duck* shooter);
    virtual Vector2D GetShootingDirection(Duck* shooter);

public:
    InstantWeapon(ProjectilesController& projectilesController, const Transform& initialSpace,
                  float scope, uint16_t ammo, uint8_t damage, float dispersionRange, float cooldown,
                  TypeProjectile typeProjectile,
                  float inclination = ShootingInclination::BASIC_NO_INCLINATION);

    virtual void BeCollected(TypeCollectable& typeOnHandRef) override = 0;
    virtual bool Use(Duck* shooter) override;
    void Update(float deltaTime) override;
    virtual ~InstantWeapon() = default;
    virtual TypeCollectable GetTypeCollectable() override = 0;
};

#endif
