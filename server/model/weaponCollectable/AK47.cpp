#include "AK47.h"

#include "server/model/Duck.h"
#include "server/model/projectile/BounceProjectile.h"

#define DISPERSION_RATE_AK47 0.3
#define RECOIL_AK47 12

AK47::AK47(ProjectilesController& controller, const Transform& initialSpace, const Config& conf):
        Weapon(controller, initialSpace, conf.getAK47Scope(), conf.getAK47Ammo(),
               conf.getDamageMedium(), conf.getShortDispersion(), conf.getCooldownBasic(),
               TypeProjectile::BULLET),
        dispersionRate(DISPERSION_RATE_AK47),
        maxDispersionRate(conf.getSuperDispersion()) {}

void AK47::IncraseDispersion() {
    if (dispersionRange + dispersionRate <= maxDispersionRate)
        dispersionRange += dispersionRate;
}


void AK47::BeCollected(TypeCollectable& collectorTypeRef) {
    collectorTypeRef = TypeCollectable::AK47;
}

void AK47::Shoot(Duck* shooter) {
    BounceProjectile* projectile =
            new BounceProjectile(shooter->GetTransform().GetPos(), GetShootingDirection(shooter),
                                 scope, damage, typeProjectile, l);
    projectilesController.RelaseProjectile(projectile);
}

TypeCollectable AK47::GetTypeCollectable() { return TypeCollectable::AK47; }

void AK47::StopUse(Duck* shooter) {
    shooter->StopShooting();
    dispersionRange = 0;
}

bool AK47::Use(Duck* shooter) {
    if (Weapon::Use(shooter)) {
        shooter->StartShooting();
        shooter->ApplyRecoil(RECOIL_AK47);
        IncraseDispersion();
        return true;
    }
    return false;
}
