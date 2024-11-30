#ifndef THROWABLE_CREATOR_H
#define THROWABLE_CREATOR_H
#include <memory>

#include "server/model/collectable/Collectable.h"

class Throwable;
class ThrowableCreator: public Collectable {
public:
    explicit ThrowableCreator(const Transform& initialSpace);

    virtual std::shared_ptr<Throwable> GetThrowable() = 0;

    virtual void BeCollected(TypeCollectable& typeOnHandRef) override = 0;
    bool Use(Duck* thrower) override;
    void StopUse(Duck* /*user*/) override {}
    void Update(float /*deltaTime*/) override;
    virtual ~ThrowableCreator() = default;
    virtual TypeCollectable GetTypeCollectable() override = 0;
};

#endif
