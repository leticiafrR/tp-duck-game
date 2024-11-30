#ifndef THROWABLE_CREATOR_H
#define THROWABLE_CREATOR_H
#include <memory>

#include "../Weapon.h"

class Throwable;


class ThrowableCreator: public Weapon {
public:
    ThrowableCreator(ProjectilesController& projectilesController, const Transform& initialSpace);

    virtual std::shared_ptr<Throwable> GetThrowable() = 0;
    virtual void BeCollected(TypeCollectable& typeOnHandRef) override = 0;
    virtual TypeCollectable GetTypeCollectable() override = 0;

    bool Use(Duck* thrower) override;
    void Update(float /*deltaTime*/) override;
    virtual ~ThrowableCreator() = default;
};


#endif
