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
    PistolaCowboy(ProjectilesController& controller, const Transform& initialSpace,
                  const Config& conf):
            InstantWeapon(controller, initialSpace, conf.getCowboyPistolScope(),
                          conf.getCowboyPistolAmmo(), conf.getDamageShort(), conf.getNoDispersion(),
                          conf.getCooldownBasic(), TypeProjectile::BULLET) {}
    // a chequear
    void BeCollected(TypeCollectable& typeOnHandRef) override {
        typeOnHandRef = TypeCollectable::COWBOY_PISTOL;
    }
};

#endif
