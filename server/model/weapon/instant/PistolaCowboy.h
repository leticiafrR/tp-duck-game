#ifndef PISTOLA_COWBOY_H
#define PISTOLA_COWBOY_H
#include "../InstantWeapon.h"

class PistolaCowboy: public InstantWeapon {
public:
    PistolaCowboy(ProjectilesController& controller, const Transform& initialSpace):
            InstantWeapon(controller, initialSpace, Scope::PISTOLA_COWBOY, Ammo::PISTOLA_COWBOY,
                          Damage::SHORT, TypeProjectile::Bullet) {}

    void BeCollected(TypeCollectable& typeOnHandRef) override {
        typeOnHandRef = TypeCollectable::PISTOLA_COWBOY;
    }
};

#endif
