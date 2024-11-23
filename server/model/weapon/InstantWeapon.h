#ifndef INSTANT_WEAPON_H
#define INSTANT_WEAPON_H

#include <random>

#include "../projectile/InstantProjectile.h"
#include "server/config.h"
#include "server/model/types.h"

#include "Weapon.h"

class InstantWeapon: public Weapon {
protected:
    // cppcheck-suppress unusedStructMember
    const float scope;
    // cppcheck-suppress unusedStructMember
    const uint8_t damage;
    // cppcheck-suppress unusedStructMember
    const float dispersionRange;
    // cppcheck-suppress unusedStructMember
    const float cooldown;
    // cppcheck-suppress unusedStructMember
    float cooldownTimer;
    // cppcheck-suppress unusedStructMember
    const uint8_t projectilesPerShot;
    // cppcheck-suppress unusedStructMember
    float inclination;
    // cppcheck-suppress unusedStructMember
    InstantProjectileEventListener* l;

    float RandomDisturbance();

public:
    virtual InstantProjectile* Shoot(Duck* shooter);
    InstantWeapon(ProjectilesController& projectilesController, const Transform& initialSpace,
                  float scope, uint16_t ammo, uint8_t damage, float dispersionRange, float cooldown,
                  TypeProjectile typeProjectile,
                  float inclination = ShootingInclination::BASIC_NO_INCLINATION,
                  uint8_t projectilesPerShot = ProjectilesPerShot::BASIC_ONE_SHOT);

    virtual void BeCollected(TypeCollectable& typeOnHandRef) override = 0;
    virtual void Use(Duck* shooter) override;
    void Update(float deltaTime) override;  // por el momento solo se usa para el cooldown
    virtual ~InstantWeapon() = default;
};
/* from this class derive:
    -> pistolaCowboy
    -> laserRifles
    -> etc
*/

#endif
