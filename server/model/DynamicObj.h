#ifndef DYNAMIC_OBJECT_H
#define DYNAMIC_OBJECT_H

#include "common/Transform.h"
#include "map/staticMap.h"

// class StaticMap;
class DynamicObject {
protected:
    Transform mySpace;
    Vector2D velocity;
    bool isDead;
    const int speedX;

public:
    virtual void ApplyGravity(StaticMap& map, float deltaTime) = 0;
    virtual void HandleCollisionWithMap(const Transform& mapT) = 0;
    virtual void HandleOutOfBounds(float displacement) = 0;
    virtual ~DynamicObject() = default;

    DynamicObject(int speedX, const Transform& mySpace);

    void CheckInteractionWithMap(StaticMap& map, float deltaTime);
    void CheckOutOfMapBoundaries(StaticMap& map);
    void CheckCollisionWithMap(StaticMap& map);
    void UpdatePosition(StaticMap& map, float deltaTime);

    void MarkAsDead();
    bool IsDead();
    const Transform& GetTransform() const;
};


/*******************************************************************************************/
/*                                DEFINITIONS                                              */
/*******************************************************************************************/

DynamicObject::DynamicObject(int speedX, const Transform& mySpace):
        mySpace(mySpace), isDead(false), speedX(speedX) {}


void DynamicObject::UpdatePosition(StaticMap& map, float deltaTime) {
    mySpace.Move(velocity * deltaTime);
    CheckInteractionWithMap(map, deltaTime);
}

void DynamicObject::CheckInteractionWithMap(StaticMap& map, float deltaTime) {
    ApplyGravity(map, deltaTime);
    CheckOutOfMapBoundaries(map);
    CheckCollisionWithMap(map);
}

void DynamicObject::CheckOutOfMapBoundaries(StaticMap& map) {
    std::optional<float> maybeDisplacement = map.DisplacementOutOfBounds(mySpace);
    if (maybeDisplacement.has_value()) {
        HandleOutOfBounds(maybeDisplacement.value());
    }
}

void DynamicObject::CheckCollisionWithMap(StaticMap& map) {
    std::optional<Transform> maybeCollision = map.CheckCollision(mySpace);
    if (maybeCollision.has_value()) {
        HandleCollisionWithMap(maybeCollision.value());
    }
}


void DynamicObject::MarkAsDead() { isDead = true; }

bool DynamicObject::IsDead() { return isDead; }

const Transform& DynamicObject::GetTransform() const { return mySpace; }

#endif
