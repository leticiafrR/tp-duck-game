#ifndef PISTOLA_COWBOY_H
#define PISTOLA_COWBOY_H
#include "../InstantWeapon.h"

class PistolaCowboy: public InstantWeapon {
    /**
     * sin disparos continuos
     * sin dispersiòn
     */
    // para esta arma es suficiente con la definiciòn estandart de de instantWeapon para generar
    // proyectiles
public:
    PistolaCowboy(ProjectilesController& controller, const Transform& initialSpace):
            InstantWeapon(controller, initialSpace, Scope::PISTOLA_COWBOY, Ammo::PISTOLA_COWBOY,
                          Damage::SHORT, DispersionRange::NO_DISPERSION, Cooldown::NONE,
                          TypeProjectile::Bullet) {}

    void BeCollected(TypeCollectable& typeOnHandRef) override {
        typeOnHandRef = TypeCollectable::PISTOLA_COWBOY;
    }
    // void Use(Duck* shooter) generico
};

#endif
