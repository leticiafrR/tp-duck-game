#ifndef DYNAMIC_OBJECT_H
#define DYNAMIC_OBJECT_H

#include <cstdint>

#include "common/Transform.h"

class StaticMap;
class DynamicObject {
protected:
    Transform mySpace;
    Vector2D velocity;
    bool isDead;

public:
    virtual void ApplyGravity(const StaticMap& map, float deltaTime) = 0;
    virtual void HandleCollisionWithMap(const Transform& mapT) = 0;
    virtual void HandleOutOfBounds(float displacement) = 0;

    virtual ~DynamicObject() = default;

    explicit DynamicObject(const Transform& mySpace);

    void CheckInteractionWithMap(const StaticMap& map, float deltaTime);
    void CheckOutOfMapBoundaries(const StaticMap& map);
    void CheckCollisionWithMap(const StaticMap& map);
    void UpdatePosition(const StaticMap& map, float deltaTime);

    void MarkAsDead();
    bool IsDead();
    const Transform& GetTransform() const;
};

#endif
