#ifndef HELMET_H
#define HELMET_H

#include "Collectable.h"
class Helmet: public Collectable {
public:
    explicit Helmet(Transform initialSpace);
    void BeCollected(TypeItem& collectorTypeRef) override;

    void StopUse(Duck* /*parameter*/) override;
    void Update(float /*deltaTime*/) override;
    TypeItem GetTypeCollectable() override;
};

#endif
