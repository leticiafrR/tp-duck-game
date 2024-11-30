#ifndef GRENADE_CREATOR_H
#define GRENADE_CREATOR_H
#include <memory>

#include "server/model/throwable/Grenade.h"

#include "ThrowableCreator.h"


/*es la unica arma que crea un projectil que recibe en el contructor el ProjectilesController*/
/*por otro lado, las bananas crean una trampa*/
class GrenadeCreator: public ThrowableCreator {

public:
    GrenadeCreator(ProjectilesController& projectilesController, const Transform& initialSpace):
            ThrowableCreator(projectilesController, initialSpace) {
        std::cout << "se spawneò en una granada\n";
    }

    std::shared_ptr<Throwable> GetThrowable() override {
        // Grenade(ProjectilesController& projectilesController)
        std::cout << "se presionò disparar teniendo un granada en mano: le sacaste el seguro. "
                     "TÌRALA\n";
        return std::make_shared<Grenade>(projectilesController);
    }

    void BeCollected(TypeCollectable& typeOnHandRef) override {
        typeOnHandRef = TypeCollectable::GRENADE;
        std::cout << "tenès una granada en mano\n";
    }

    TypeCollectable GetTypeCollectable() override { return TypeCollectable::GRENADE; }

    ~GrenadeCreator() = default;
};


#endif
