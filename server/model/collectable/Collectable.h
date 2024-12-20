#ifndef COLLECTABLE_H
#define COLLECTABLE_H
#include <vector>

#include "common/Transform.h"
#include "data/snapshot.h"

class CollectableEventListener;
class Duck;
class StaticMap;

class Collectable {
protected:
    Transform mySpace;

public:
    explicit Collectable(const Transform& initialSpace);
    virtual ~Collectable() = default;

    void BeDropped(const Vector2D& duckPosition);
    virtual bool Use(Duck* user);
    virtual void StopUse(Duck* user) = 0;
    virtual void Update(float deltaTime) = 0;

    virtual void BeCollected(TypeItem& itemInHandRef) = 0;
    virtual TypeItem GetTypeCollectable() = 0;
    Transform& GetTransform();
    virtual bool StillReusable();
};

#endif
