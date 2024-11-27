#include "CollectableWrapper.h"

CollectableWrapper::CollectableWrapper(std::shared_ptr<Collectable> collectable,
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

std::shared_ptr<Collectable> CollectableWrapper::GetCollectable() { return collectable; }
