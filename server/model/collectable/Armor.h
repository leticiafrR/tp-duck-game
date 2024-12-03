#ifndef ARMOR_H
#define ARMOR_H

#include "Collectable.h"

class Armor: public Collectable {
public:
    explicit Armor(Transform initialSpace);
    void BeCollected(TypeItem& collectorTypeRef) override;
    void StopUse(Duck* /*user*/) override;
    void Update(float /*deltaTime*/) override;
    TypeItem GetTypeCollectable() override;
};

#endif
