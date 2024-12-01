#ifndef ARMOR_H
#define ARMOR_H
#include "../Duck.h"

#include "Collectable.h"
class Armor: public Collectable {
public:
    explicit Armor(Transform initialSpace): Collectable(initialSpace) {}
    void BeCollected(TypeCollectable& collectorTypeRef) override {
        collectorTypeRef = TypeCollectable::ARMOR;
    }

    void StopUse(Duck* /*user*/) override {}
    void Update(float /*deltaTime*/) override {}
    TypeCollectable GetTypeCollectable() override { return TypeCollectable::ARMOR; }
};

#endif
