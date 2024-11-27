#include "PewPewLaser.h"
#define CUSTOM_DAMAGE(x) ((x) / 9)

PewPewLaser::PewPewLaser(ProjectilesController& controller, const Transform& initialSpace,
                         const Config& conf):
        InstantWeapon(controller, initialSpace, conf.getPewPewLaserScope(),
                      conf.getPewPewLaserAmmo(), CUSTOM_DAMAGE(conf.getDamageShort()),
                      conf.getNoDispersion(), conf.getCooldownBasic(), TypeProjectile::LASER,
                      conf.getHiperDispersion()) {}


void PewPewLaser::BeCollected(TypeCollectable& collectorTypeRef) {
    collectorTypeRef = TypeCollectable::PEW_PEW_LASER;
    std::cout << "[pewpew] recogiste una pewpew GRRRR\n";
}

void PewPewLaser::Shoot(Duck* shooter) {
    float originalInclination = inclination;
    for (int i = -1; i < 2; i++) {
        InstantProjectile* projectile = new InstantProjectile(shooter->GetTransform().GetPos(),
                                                              GetShootingDirection(shooter), scope,
                                                              damage, typeProjectile, l);
        projectilesController.RelaseProjectile(projectile);
        inclination *= i;
    }
    inclination = originalInclination;
}

TypeCollectable PewPewLaser::GetTypeCollectable() { return TypeCollectable::PEW_PEW_LASER; }
