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
    const int speedX;
    int life;

public:
    virtual void ApplyGravity(StaticMap& map, float deltaTime) = 0;
    virtual void HandleCollisionWithMap(const Transform& mapT) = 0;
    virtual void HandleOutOfBounds(float displacement) = 0;
    virtual void HandleDead();
    virtual void HandleReceiveDamage(uint8_t damage);

    virtual ~DynamicObject() = default;

    DynamicObject(int speedX, const Transform& mySpace, int life);

    void CheckInteractionWithMap(StaticMap& map, float deltaTime);
    void CheckOutOfMapBoundaries(StaticMap& map);
    void CheckCollisionWithMap(StaticMap& map);
    void UpdatePosition(StaticMap& map, float deltaTime);

    void MarkAsDead();
    bool IsDead();
    const Transform& GetTransform() const;
};

#endif
