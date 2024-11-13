#ifndef COLLECTABLE_H
#define COLLECTABLE_H
#include "common/Transform.h"

class Duck;
enum class TypeCollectable;

class Collectable {
protected:
    Transform mySpace;

public:
    explicit Collectable(const Transform& initialSpace): mySpace(initialSpace) {}
    virtual ~Collectable() = default;

    const Transform& GetTransform() const { return mySpace; }
    void BeDropped(const Vector2D& position) { mySpace.SetPos(position); }


    virtual void BeCollected(TypeCollectable& collectorTyperRef) = 0;
    virtual void Use(Duck* user) = 0;
};


#endif
