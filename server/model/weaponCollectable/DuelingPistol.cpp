#include "DuelingPistol.h"

#include "server/model/Duck.h"
DuelingPistol::DuelingPistol(ProjectilesController& controller, const Transform& initialSpace,
                             const Config& conf):
        Weapon(controller, initialSpace, conf.getDuelingPistolScope(), conf.getDuelingPistolAmmo(),
               conf.getDamageLong(), conf.getSuperDispersion(), conf.getCooldownBasic(),
               TypeProjectile::BULLET) {}


void DuelingPistol::BeCollected(TypeCollectable& collectorTypeRef) {
    collectorTypeRef = TypeCollectable::DUELING_PISTOL;
}

bool DuelingPistol::Use(Duck* shooter) {
    shooter->StartShooting();
    return Weapon::Use(shooter);
}

TypeCollectable DuelingPistol::GetTypeCollectable() { return TypeCollectable::DUELING_PISTOL; }
