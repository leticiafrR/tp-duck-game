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
    virtual void Update(float deltaTime, StaticMap& map) = 0;

    virtual void BeCollected(TypeCollectable& itemInHandRef) = 0;
    virtual TypeCollectable GetTypeCollectable() = 0;
    const Transform& GetTransform() const;
    virtual bool StillReusable();
};

#endif
