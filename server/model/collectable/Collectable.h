#ifndef COLLECTABLE_H
#define COLLECTABLE_H
#include <vector>

#include "common/Transform.h"
#include "data/snapshot.h"

class CollectableEventListener;
class Duck;

class Collectable {
protected:
    Transform mySpace;

public:
    explicit Collectable(const Transform& initialSpace): mySpace(initialSpace) {}
    virtual ~Collectable() = default;


    virtual void BeDropped(const Vector2D& duckPosition) { mySpace.SetPos(duckPosition); }

    virtual bool Use(Duck* user) = 0;
    virtual void StopUse(Duck* user) = 0;
    virtual void Update(float deltaTime) = 0;

    virtual void BeCollected(TypeCollectable& itemInHandRef) = 0;
    virtual TypeCollectable GetTypeCollectable() = 0;
    const Transform& GetTransform() const { return mySpace; }
    virtual bool StillReusable() = 0;
};


#endif
