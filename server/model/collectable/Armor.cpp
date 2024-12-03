#include "Armor.h"

Armor::Armor(Transform initialSpace): Collectable(initialSpace) {}
void Armor::BeCollected(TypeItem& collectorTypeRef) { collectorTypeRef = TypeItem::ARMOR; }

void Armor::StopUse(Duck* /*user*/) {}
void Armor::Update(float /*deltaTime*/) {}
TypeItem Armor::GetTypeCollectable() { return TypeItem::ARMOR; }
