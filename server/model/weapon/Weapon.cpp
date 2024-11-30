#include "Weapon.h"

#include <cstdint>

#include "server/model/Duck.h"


Weapon::Weapon(ProjectilesController& projectilesController, const Transform& initialSpace,
               uint16_t ammo):
        Collectable(initialSpace), projectilesController(projectilesController), ammo(ammo) {}

void Weapon::StopUse(Duck* shooter) { shooter->StopShooting(); }

bool Weapon::StillReusable() { return ammo > 0; }
