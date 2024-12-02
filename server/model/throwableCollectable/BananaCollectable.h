#ifndef BANANA_COLLECTABLE_H
#define BANANA_COLLECTABLE_H
#include <memory>

#include "ThrowableCollectable.h"

class BananaCollectable: public ThrowableCollectable {
public:
    explicit BananaCollectable(const Transform& initialSpace);
    void BeCollected(TypeCollectable& typeOnHandRef) override;
    TypeCollectable GetTypeCollectable() override;
    bool Use(Duck* thrower) override;
    ~BananaCollectable() = default;
};
#endif
