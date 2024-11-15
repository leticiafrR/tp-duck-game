#ifndef PISTOLA_COWBOY_H
#define PISTOLA_COWBOY_H
#include "../InstantWeapon.h"

class PistolaCowboy: public InstantWeapon {
    /*requiere presionar el botòn de disparo por cada tiro,
    arma sin dispersiòn, ni retroceso, ni tiempo de enfriamiento o recarga*/

public:
    PistolaCowboy(ProjectilesController& controller, const Transform& initialSpace):
            InstantWeapon(controller, initialSpace, Scope::PISTOLA_COWBOY, Ammo::PISTOLA_COWBOY,
                          Damage::SHORT, TypeProjectile::Bullet) {}

    void BeCollected(TypeCollectable& typeOnHandRef) override {
        typeOnHandRef = TypeCollectable::PISTOLA_COWBOY;
    }

    // void Use(Duck* shooter) override {

    //     /*logica particular del arma (si aplica un retroceso o debe actualizar un contador o algo
    //      * especial, aqui se realizarìa)*/

    // }
};

#endif
