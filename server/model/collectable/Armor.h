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
    bool Use(Duck* user) override {
        user->TryEquip(TypeCollectable::ARMOR);
        return true;
    }

    void StopUse(Duck* /*parameter*/) override {}
    void Update(float /*parameter*/) override {}
    bool StillReusable() override { return true; }
    TypeCollectable GetTypeCollectable() override { return TypeCollectable::ARMOR; }
};

#endif
