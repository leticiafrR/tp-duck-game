#include "Magnum.h"

#include "../physicsConstants.h"
#include "server/model/Duck.h"

Magnum::Magnum(ProjectilesController& controller, const Transform& initialSpace,
               const Config& conf):
        Weapon(controller, initialSpace, conf.getMagnumScope(), conf.getMagnumAmmo(),
               conf.getDamageLong(), conf.getShortDispersion(), conf.getCooldownBasic(),
               TypeProjectile::BULLET) {}

void Magnum::BeCollected(TypeItem& typeOnHandRef) { typeOnHandRef = TypeItem::MAGNUM; }

TypeItem Magnum::GetTypeCollectable() { return TypeItem::MAGNUM; }

bool Magnum::Use(Duck* shooter) {
    shooter->StartShooting();
    bool ret = Weapon::Use(shooter);
    if (ret)
        shooter->ApplyRecoil(RECOIL_MAGNUM);
    shooter->StopShooting();
    return ret;
}
