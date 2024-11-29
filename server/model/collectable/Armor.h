#ifndef ARMOR_H
#define ARMOR_H
#include "../Duck.h"

#include "Collectable.h"
class Armor: public Collectable {
public:
    explicit Armor(Transform initialSpace): Collectable(initialSpace) {}
    void BeCollected(TypeCollectable& collectorTypeRef) override {
        collectorTypeRef = TypeCollectable::ARMOR;
        std::cout << "armor collected\n";
    }

    void StopUse(Duck* /*user*/) override {}
    void Update(float /*deltaTime*/, StaticMap& /*map*/) override {}
    TypeCollectable GetTypeCollectable() override { return TypeCollectable::ARMOR; }
};

#endif
