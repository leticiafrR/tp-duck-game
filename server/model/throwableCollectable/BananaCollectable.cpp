#include "BananaCollectable.h"

#include "server/model/throwable/Banana.h"

BananaCollectable::BananaCollectable(const Transform& initialSpace):
        ThrowableCollectable(initialSpace) {}
std::shared_ptr<Throwable> BananaCollectable::GetThrowable() { return std::make_shared<Banana>(); }
void BananaCollectable::BeCollected(TypeCollectable& typeOnHandRef) {
    typeOnHandRef = TypeCollectable::BANANA;
}
TypeCollectable BananaCollectable::GetTypeCollectable() { return TypeCollectable::BANANA; }
