#include "CollectableWrapper.h"

CollectableWrapper::CollectableWrapper(Collectable* collectable,
                                       std::shared_ptr<float> sourceTimer):
        sourceTimer(sourceTimer), collectable(collectable) {}


void CollectableWrapper::BeCollected(TypeCollectable& itemInHandRef) {
    if (sourceTimer) {
        *sourceTimer = 0;
        sourceTimer.reset();
        std::cout << "se reinicia contador\n";
    }
    collectable->BeCollected(itemInHandRef);
}
const Transform& CollectableWrapper::GetTransform() const { return collectable->GetTransform(); }

Collectable* CollectableWrapper::GetCollectable() { return collectable; }
