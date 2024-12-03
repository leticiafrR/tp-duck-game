#include "Shotgun.h"

#include "server/model/Duck.h"
#include "server/model/physicsConstants.h"
#include "server/model/projectile/Projectile.h"

Shotgun::Shotgun(ProjectilesController& controller, const Transform& initialSpace,
                 const Config& conf):
        Weapon(controller, initialSpace, conf.getShotgunScope(),
               AMMO_WITH_RELOAD(conf.getShotgunAmmo()), conf.getDamageShort(),
               conf.getLongDispersion(), conf.getCooldownBasic(), TypeProjectile::FRAGMENT),
        ammoLoaded(true) {}


void Shotgun::BeCollected(TypeItem& collectorTypeRef) { collectorTypeRef = TypeItem::SHOTGUN; }

void Shotgun::Shoot(Duck* shooter) {
    if (ammoLoaded) {
        shooter->StartShooting();
        for (int i = 0; i < 6; i++) {
            Projectile* projectile =
                    new Projectile(shooter->GetTransform().GetPos(), GetShootingDirection(shooter),
                                   scope, damage, typeProjectile, l);
            projectilesController.RelaseProjectile(projectile);
        }
        ammoLoaded = false;
    } else {
        ammoLoaded = true;
    }
}

TypeItem Shotgun::GetTypeCollectable() { return TypeItem::SHOTGUN; }
