#include "ThrowableCreator.h"

#include "server/model/Duck.h"

ThrowableCreator::ThrowableCreator(ProjectilesController& projectilesController,
                                   const Transform& initialSpace):
        Weapon(projectilesController, initialSpace, 1) {}


bool ThrowableCreator::Use(Duck* thrower) {
    if (ammo > 0) {
        std::shared_ptr<Throwable> throwable = GetThrowable();
        thrower->PrepareToThrow(throwable);
        // ningun creador de arrojables en realidad los arroja
        std::cout << "DISPARASTE: ahora el duck no tiene un collectable, Tiene un arrojable\n";
        ammo--;
        return true;
    }
    return false;
}

void ThrowableCreator::Update(float /*deltaTime*/) {}
