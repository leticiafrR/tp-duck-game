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

    void StopUse(Duck* /*user*/) override {}
    void Update(float /*deltaTime*/, StaticMap& /*map*/) override {}
    bool StillReusable() override { return true; }
    TypeCollectable GetTypeCollectable() override { return TypeCollectable::ARMOR; }
    void BeDropped(const Vector2D& duckPosition, const Vector2D& /*direction*/) override {
        mySpace.SetPos(duckPosition);
    }
};

#endif
