#ifndef HELMET_H
#define HELMET_H

#include "../Duck.h"

#include "Collectable.h"
class Helmet: public Collectable {
public:
    explicit Helmet(Transform initialSpace): Collectable(initialSpace) {}
    void BeCollected(TypeItem& collectorTypeRef) override { collectorTypeRef = TypeItem::HELMET; }

    void StopUse(Duck* /*parameter*/) override {}
    void Update(float /*deltaTime*/) override {}
    TypeItem GetTypeCollectable() override { return TypeItem::HELMET; }
};

#endif
