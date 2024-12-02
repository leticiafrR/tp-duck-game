#ifndef DYNAMIC_OBJECT_H
#define DYNAMIC_OBJECT_H

#include <cstdint>

#include "common/Transform.h"

class StaticMap;
class DynamicObject {
private:
    void CheckInteractionWithMap(const StaticMap& map, float deltaTime);
    void CheckOutOfMapBoundaries(const StaticMap& map);

protected:
    Transform mySpace;
    Vector2D velocity;
    bool isDead;
    virtual void ApplyGravity(const StaticMap& map, float deltaTime) = 0;
    virtual void HandleCollisionWithMap(const Transform& mapT) = 0;
    virtual void HandleOutOfBounds(float displacement) = 0;
    void CheckCollisionWithMap(const StaticMap& map);

public:
    virtual ~DynamicObject() = default;
    explicit DynamicObject(const Transform& mySpace);
    void UpdatePosition(const StaticMap& map, float deltaTime);
    void MarkAsDead();
    bool IsDead();
    const Transform& GetTransform() const;
};

#endif
