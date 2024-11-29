#ifndef WEAPON_H
#define WEAPON_H
#include <cstdint>

#include "../Duck.h"
#include "../collectable/Collectable.h"
#include "../projectile/Projectile.h"
#include "../projectile/ProjectilesController.h"

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
    virtual bool Use(Duck* shooter) override = 0;
    virtual void StopUse(Duck* shooter) override { shooter->StopShooting(); }
    virtual void Update(float deltaTime) override = 0;
    virtual ~Weapon() = default;
    virtual TypeCollectable GetTypeCollectable() override = 0;
    bool StillReusable() override { return ammo > 0; }
};

/*de esta derivan:
    -> hitscanWeapon
    -> physicalWeapon
*/

#endif
