#include "Shotgun.h"

#include "server/model/Duck.h"
#include "server/model/projectile/instant/InstantProjectile.h"
Shotgun::Shotgun(ProjectilesController& controller, const Transform& initialSpace,
                 const Config& conf):
        InstantWeapon(controller, initialSpace, conf.getShotgunScope(),
                      AMMO_WITH_RELOAD(conf.getShotgunAmmo()), conf.getDamageShort(),
                      conf.getLongDispersion(), conf.getCooldownBasic(), TypeProjectile::BULLET),
        ammoLoaded(true) {}


void Shotgun::BeCollected(TypeCollectable& collectorTypeRef) {
    collectorTypeRef = TypeCollectable::SHOTGUN;
}

void Shotgun::Shoot(Duck* shooter) {
    if (ammoLoaded) {
        shooter->StartShooting();
        for (int i = 0; i < 6; i++) {
            InstantProjectile* projectile = new InstantProjectile(shooter->GetTransform().GetPos(),
                                                                  GetShootingDirection(shooter),
                                                                  scope, damage, typeProjectile, l);
            projectilesController.RelaseInstantProjectile(projectile);
        }
        ammoLoaded = false;
    } else {
        ammoLoaded = true;
    }
}

TypeCollectable Shotgun::GetTypeCollectable() { return TypeCollectable::SHOTGUN; }
