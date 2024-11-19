#ifndef WEAPON_H
#define WEAPON_H
#include <cstdint>

#include "../Duck.h"
#include "../collectable/Collectable.h"
#include "../projectile/Projectile.h"
#include "../projectile/ProjectilesController.h"
#include "../types.h"

class Weapon: public Collectable {
protected:
    ProjectilesController& projectilesController;
    uint16_t ammo;
    TypeProjectile typeProjectile;

public:
    Weapon(ProjectilesController& projectilesController, const Transform& initialSpace,
           uint16_t ammo, TypeProjectile typeProjectile):
            Collectable(initialSpace),
            projectilesController(projectilesController),
            ammo(ammo),
            typeProjectile(typeProjectile) {}

    virtual void BeCollected(TypeCollectable& typeOnHandRef) override = 0;
    virtual void Use(Duck* shooter) override { shooter->StartShooting(); };
    virtual void StopUse(Duck* shooter) override { shooter->StopShooting(); }
    virtual ~Weapon() = default;
};

/*de esta derivan:
    -> hitscanWeapon
    -> physicalWeapon
*/

#endif
