#ifndef BANANA_COLLECTABLE_H
#define BANANA_COLLECTABLE_H
#include <memory>

#include "ThrowableCollectable.h"


class BananaCollectable: public ThrowableCollectable {
public:
    explicit BananaCollectable(const Transform& initialSpace);
    std::shared_ptr<Throwable> GetThrowable() override;
    void BeCollected(TypeCollectable& typeOnHandRef) override;
    TypeCollectable GetTypeCollectable() override;
    ~BananaCollectable() = default;
};
#endif
