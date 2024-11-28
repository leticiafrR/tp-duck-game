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
    bool Use(Duck* user) override {
        user->TryEquip(TypeCollectable::HELMET);
        return true;
    }

    void StopUse(Duck* /*parameter*/) override {}
    void Update(float /*parameter*/) override {}
    bool StillReusable() override { return true; }
    TypeCollectable GetTypeCollectable() override { return TypeCollectable::HELMET; }
};

#endif
