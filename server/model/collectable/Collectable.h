#ifndef COLLECTABLE_H
#define COLLECTABLE_H
#include "common/Transform.h"
#include "data/snapshot.h"

class Duck;

class Collectable {
protected:
    Transform mySpace;

public:
    explicit Collectable(const Transform& initialSpace): mySpace(initialSpace) {}
    virtual ~Collectable() = default;

    const Transform& GetTransform() const { return mySpace; }
    void BeDropped(const Vector2D& position) { mySpace.SetPos(position); }


    virtual void BeCollected(TypeCollectable& itemInHandRef) = 0;
    virtual void Use(Duck* user) = 0;
    virtual void StopUse(Duck* user) = 0;
    virtual void Update(float deltaTime) = 0;
};


#endif
