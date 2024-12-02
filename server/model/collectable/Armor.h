#ifndef ARMOR_H
#define ARMOR_H
#include "../Duck.h"

#include "Collectable.h"
class Armor: public Collectable {
public:
    explicit Armor(Transform initialSpace): Collectable(initialSpace) {}
    void BeCollected(TypeItem& collectorTypeRef) override { collectorTypeRef = TypeItem::ARMOR; }

    void StopUse(Duck* /*user*/) override {}
    void Update(float /*deltaTime*/) override {}
    TypeItem GetTypeCollectable() override { return TypeItem::ARMOR; }
};

#endif
