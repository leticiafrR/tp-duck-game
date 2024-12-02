#include "BananaCollectable.h"

#include "server/model/Duck.h"
#include "server/model/throwable/Banana.h"

BananaCollectable::BananaCollectable(const Transform& initialSpace):
        ThrowableCollectable(initialSpace) {}

void BananaCollectable::BeCollected(TypeItem& typeOnHandRef) { typeOnHandRef = TypeItem::BANANA; }

TypeItem BananaCollectable::GetTypeCollectable() { return TypeItem::BANANA; }

bool BananaCollectable::Use(Duck* thrower) {
    thrower->PrepareToThrow(std::make_shared<Banana>(TypeItem::BANANA_PEEL), TypeItem::BANANA_PEEL);
    return true;
}
