#ifndef COLLECTABLE_WRAPPER_H
#define COLLECTABLE_WRAPPER_H
#include <memory>

#include "Collectable.h"

class CollectableWrapper {
private:
    std::shared_ptr<float> sourceTimer;
    std::shared_ptr<Collectable> collectable;

public:
    CollectableWrapper() = default;
    CollectableWrapper(std::shared_ptr<Collectable> collectable,
                       std::shared_ptr<float> sourceTimer);
    void BeCollected(TypeCollectable& itemInHandRef);
    const Transform& GetTransform() const;

    std::shared_ptr<Collectable> GetCollectable();
};

#endif
