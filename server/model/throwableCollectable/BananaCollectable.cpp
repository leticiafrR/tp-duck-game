#include "BananaCollectable.h"

#include "server/model/Duck.h"
#include "server/model/throwable/Banana.h"

BananaCollectable::BananaCollectable(const Transform& initialSpace):
        ThrowableCollectable(initialSpace) {}

void BananaCollectable::BeCollected(TypeCollectable& typeOnHandRef) {
    typeOnHandRef = TypeCollectable::BANANA;
}

TypeCollectable BananaCollectable::GetTypeCollectable() { return TypeCollectable::BANANA; }

bool BananaCollectable::Use(Duck* thrower) {
    thrower->PrepareToThrow(std::make_shared<Banana>(TypeCollectable::BANANA_PEEL),
                            TypeCollectable::BANANA_PEEL);
    return true;
}
