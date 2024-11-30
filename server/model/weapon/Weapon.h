#ifndef WEAPON_H
#define WEAPON_H
#include <cstdint>

#include "server/model/collectable/Collectable.h"
#include "server/model/projectile/ProjectilesController.h"

class Weapon: public Collectable {
protected:
    ProjectilesController& projectilesController;
    uint16_t ammo;

public:
    Weapon(ProjectilesController& projectilesController, const Transform& initialSpace,
           uint16_t ammo);

    virtual void BeCollected(TypeCollectable& typeOnHandRef) override = 0;  // CHECK
    virtual bool Use(Duck* shooter) override = 0;
    virtual void StopUse(Duck* shooter) override;
    virtual void Update(float deltaTime) override = 0;  // CHECK
    virtual ~Weapon() = default;
    virtual TypeCollectable GetTypeCollectable() override = 0;
    bool StillReusable() override;
};


#endif
