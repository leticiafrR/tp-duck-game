#include "PistolaCowboy.h"
PistolaCowboy::PistolaCowboy(ProjectilesController& controller, const Transform& initialSpace,
                             const Config& conf):
        InstantWeapon(controller, initialSpace, conf.getCowboyPistolScope(),
                      conf.getCowboyPistolAmmo(), conf.getDamageShort(), conf.getNoDispersion(),
                      conf.getCooldownBasic(), TypeProjectile::BULLET) {}

void PistolaCowboy::BeCollected(TypeCollectable& typeOnHandRef) {
    typeOnHandRef = TypeCollectable::COWBOY_PISTOL;
}

TypeCollectable PistolaCowboy::GetTypeCollectable() { return TypeCollectable::COWBOY_PISTOL; }
