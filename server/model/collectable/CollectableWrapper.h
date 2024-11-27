#ifndef COLLECTABLE_WRAPPER_H
#define COLLECTABLE_WRAPPER_H
#include "Collectable.h"

class CollectableWrapper {
private:
    float* sourceTimer;
    Collectable* collectable;

public:
    CollectableWrapper() = default;
    CollectableWrapper(Collectable* collectable, float* sourceTimer);
    void BeCollected(TypeCollectable& itemInHandRef);
    const Transform& GetTransform() const;

    Collectable* GetCollectable();
};

#endif
