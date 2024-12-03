#ifndef THROWABLE_COLLECTABLE_H
#define THROWABLE_COLLECTABLE_H

#include "server/model/collectable/Collectable.h"
class ThrowableCollectable: public Collectable {

public:
    explicit ThrowableCollectable(const Transform& initialSpace);

    virtual void BeCollected(TypeItem& typeOnHandRef) override = 0;
    virtual bool Use(Duck* thrower) override = 0;
    virtual TypeItem GetTypeCollectable() override = 0;


    void StopUse(Duck* /*user*/) override;
    void Update(float /*deltaTime*/) override;
    virtual ~ThrowableCollectable() = default;
};

#endif
