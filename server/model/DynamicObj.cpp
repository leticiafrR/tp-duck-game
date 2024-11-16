#include "DynamicObj.h"

#include "map/staticMap.h"
/*******************************************************************************************/
/*                                DEFINITIONS                                              */
/*******************************************************************************************/

DynamicObject::DynamicObject(int speedX, const Transform& mySpace, int life):
        mySpace(mySpace), isDead(false), speedX(speedX), life(life) {}


void DynamicObject::HandleReceiveDamage(uint8_t damage) {
    life -= damage;
    if (life <= 0) {
        HandleDead();
    }
}

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
