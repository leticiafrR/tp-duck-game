#ifndef INSTANT_WEAPON_H
#define INSTANT_WEAPON_H

#include "../projectile/InstantProjectile.h"

#include "Weapon.h"

class InstantWeapon: public Weapon {
protected:
    const float scope;
    const uint8_t damage;
    InstantProjectileEventListener* l;

public:
    InstantWeapon(ProjectilesController& projectilesController, const Transform& initialSpace,
                  float scope, uint16_t ammo, uint8_t damage, TypeProjectile typeProjectile):
            Weapon(projectilesController, initialSpace, ammo, typeProjectile),
            scope(scope),
            damage(damage),
            l(projectilesController.GetInstantProjectileListener()) {}


    virtual void BeCollected(TypeCollectable& typeOnHandRef) override = 0;

    virtual void Use(Duck* shooter) override {
        if (ammo > 0) {
            InstantProjectile* p =
                    new InstantProjectile(shooter->GetTransform().GetPos(), shooter->GetFlip(),
                                          scope, damage, typeProjectile, l);
            projectilesController.RelaseProjectile(p);
            ammo--;
        }
    }

    virtual ~InstantWeapon() = default;

    /* from this class derive:
        -> pistolaCowboy
        -> laserRifles
        -> etc
    */
};

#endif
