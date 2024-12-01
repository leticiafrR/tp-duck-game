#ifndef PISTOLA_COWBOY_H
#define PISTOLA_COWBOY_H
#include "Weapon.h"

class PistolaCowboy: public Weapon {
public:
    PistolaCowboy(ProjectilesController& controller, const Transform& initialSpace,
                  const Config& conf);
    void BeCollected(TypeCollectable& typeOnHandRef) override;
    TypeCollectable GetTypeCollectable() override;
};

#endif
