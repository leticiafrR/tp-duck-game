#include "Helmet.h"

Helmet::Helmet(Transform initialSpace): Collectable(initialSpace) {}
void Helmet::BeCollected(TypeItem& collectorTypeRef) { collectorTypeRef = TypeItem::HELMET; }

void Helmet::StopUse(Duck* /*parameter*/) {}
void Helmet::Update(float /*deltaTime*/) {}
TypeItem Helmet::GetTypeCollectable() { return TypeItem::HELMET; }
