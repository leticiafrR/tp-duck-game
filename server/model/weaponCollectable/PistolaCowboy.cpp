#include "PistolaCowboy.h"
PistolaCowboy::PistolaCowboy(ProjectilesController& controller, const Transform& initialSpace,
                             const Config& conf):
        Weapon(controller, initialSpace, conf.getCowboyPistolScope(), conf.getCowboyPistolAmmo(),
               conf.getDamageLong(), conf.getNoDispersion(), conf.getCooldownBasic(),
               TypeProjectile::BULLET) {}

void PistolaCowboy::BeCollected(TypeItem& typeOnHandRef) {
    typeOnHandRef = TypeItem::COWBOY_PISTOL;
}

TypeItem PistolaCowboy::GetTypeCollectable() { return TypeItem::COWBOY_PISTOL; }
