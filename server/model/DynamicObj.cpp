#include "DynamicObj.h"

#include "map/staticMap.h"
/*******************************************************************************************/
/*                                DEFINITIONS                                              */
/*******************************************************************************************/

DynamicObject::DynamicObject(const Transform& mySpace): mySpace(mySpace), isDead(false) {}


void DynamicObject::UpdatePosition(const StaticMap& map, float deltaTime) {
    mySpace.Move(velocity * deltaTime);
    CheckInteractionWithMap(map, deltaTime);
}

void DynamicObject::CheckInteractionWithMap(const StaticMap& map, float deltaTime) {
    ApplyGravity(map, deltaTime);
    CheckOutOfMapBoundaries(map);
    CheckCollisionWithMap(map);
}

void DynamicObject::CheckOutOfMapBoundaries(const StaticMap& map) {
    std::optional<float> maybeDisplacement = map.DisplacementOutOfBounds(mySpace);
    if (maybeDisplacement.has_value()) {
        HandleOutOfBounds(maybeDisplacement.value());
    }
}

void DynamicObject::CheckCollisionWithMap(const StaticMap& map) {
    std::optional<Transform> maybeCollision = map.CheckCollision(mySpace);
    while (maybeCollision.has_value()) {
        HandleCollisionWithMap(maybeCollision.value());
        maybeCollision = map.CheckCollision(mySpace);
    }
}

void DynamicObject::MarkAsDead() { isDead = true; }

bool DynamicObject::IsDead() { return isDead; }

const Transform& DynamicObject::GetTransform() const { return mySpace; }
