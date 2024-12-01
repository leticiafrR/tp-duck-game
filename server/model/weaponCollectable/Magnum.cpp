#include "Magnum.h"

#include "server/model/Duck.h"
#define RECOIL_MAGNUM 12
Magnum::Magnum(ProjectilesController& controller, const Transform& initialSpace,
               const Config& conf):
        Weapon(controller, initialSpace, conf.getMagnumScope(), conf.getMagnumAmmo(),
               conf.getDamageLong(), conf.getShortDispersion(), conf.getCooldownBasic(),
               TypeProjectile::BULLET) {}

void Magnum::BeCollected(TypeCollectable& typeOnHandRef) {
    typeOnHandRef = TypeCollectable::MAGNUM;
}

TypeCollectable Magnum::GetTypeCollectable() { return TypeCollectable::MAGNUM; }

bool Magnum::Use(Duck* shooter) {
    shooter->StartShooting();
    bool ret = Weapon::Use(shooter);
    if (ret)
        shooter->ApplyRecoil(RECOIL_MAGNUM);
    shooter->StopShooting();
    return ret;
}
