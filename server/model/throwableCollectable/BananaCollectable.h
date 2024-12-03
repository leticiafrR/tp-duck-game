#ifndef BANANA_COLLECTABLE_H
#define BANANA_COLLECTABLE_H


#include "ThrowableCollectable.h"

class BananaCollectable: public ThrowableCollectable {
public:
    explicit BananaCollectable(const Transform& initialSpace);
    void BeCollected(TypeItem& typeOnHandRef) override;
    TypeItem GetTypeCollectable() override;
    bool Use(Duck* thrower) override;
    ~BananaCollectable() = default;
};
#endif
