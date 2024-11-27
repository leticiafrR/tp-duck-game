#include "DuelingPistol.h"
DuelingPistol::DuelingPistol(ProjectilesController& controller, const Transform& initialSpace,
                             const Config& conf):
        InstantWeapon(controller, initialSpace, conf.getDuelingPistolScope(),
                      conf.getDuelingPistolAmmo(), conf.getDamageLong(), conf.getSuperDispersion(),
                      conf.getCooldownBasic(), TypeProjectile::BULLET) {}


void DuelingPistol::BeCollected(TypeCollectable& collectorTypeRef) {
    collectorTypeRef = TypeCollectable::DUELING_PISTOL;
}

bool DuelingPistol::Use(Duck* shooter) {
    shooter->StartShooting();
    return InstantWeapon::Use(shooter);
}

TypeCollectable DuelingPistol::GetTypeCollectable() { return TypeCollectable::DUELING_PISTOL; }
