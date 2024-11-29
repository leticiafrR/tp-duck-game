#ifndef HELMET_H
#define HELMET_H

#include "../Duck.h"

#include "Collectable.h"
class Helmet: public Collectable {
public:
    explicit Helmet(Transform initialSpace): Collectable(initialSpace) {}
    void BeCollected(TypeCollectable& collectorTypeRef) override {
        collectorTypeRef = TypeCollectable::HELMET;
    }

    void StopUse(Duck* /*parameter*/) override {}
    void Update(float /*deltaTime*/, StaticMap& /*map*/) override {}
    TypeCollectable GetTypeCollectable() override { return TypeCollectable::HELMET; }
};

#endif
