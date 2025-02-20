#include "PewPewLaser.h"

#include "../physicsConstants.h"
#include "server/model/Duck.h"
#include "server/model/projectile/Projectile.h"


PewPewLaser::PewPewLaser(ProjectilesController& controller, const Transform& initialSpace,
                         const Config& conf):
        Weapon(controller, initialSpace, conf.getPewPewLaserScope(), conf.getPewPewLaserAmmo(),
               DAMAGE_MULTIPLES_PROJECTILES(conf.getDamageShort()), conf.getNoDispersion(),
               conf.getCooldownBasic(), TypeProjectile::LASER, conf.getHiperDispersion()) {}


void PewPewLaser::BeCollected(TypeItem& collectorTypeRef) {
    collectorTypeRef = TypeItem::PEW_PEW_LASER;
}

void PewPewLaser::Shoot(Duck* shooter) {
    float originalInclination = inclination;
    for (int i = -1; i < 2; i++) {
        Projectile* projectile =
                new Projectile(shooter->GetTransform().GetPos(), GetShootingDirection(shooter),
                               scope, damage, typeProjectile, l);
        projectilesController.RelaseProjectile(projectile);
        inclination *= i;
    }
    inclination = originalInclination;
}

TypeItem PewPewLaser::GetTypeCollectable() { return TypeItem::PEW_PEW_LASER; }
