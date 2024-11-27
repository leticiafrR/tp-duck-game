#ifndef PISTOLA_COWBOY_H
#define PISTOLA_COWBOY_H
#include "../InstantWeapon.h"

class PistolaCowboy: public InstantWeapon {
public:
    PistolaCowboy(ProjectilesController& controller, const Transform& initialSpace,
                  const Config& conf);
    void BeCollected(TypeCollectable& typeOnHandRef) override;
    TypeCollectable GetTypeCollectable() override;
};

#endif
