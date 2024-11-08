#include "DynamicObj.h"

#include "map/staticMap.h"
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

void DynamicObject::CheckCollisionWithMap(StaticMap& map, bool fromGravity) {
    std::optional<Transform> maybeCollision = map.CheckCollision(mySpace);
    if (maybeCollision.has_value()) {
        if (fromGravity) {
            std::cout << "[CheckCollisionWithMap-fromGravity]: Before correcting:\n";
            std::cout << "**** My pos: (" << mySpace.GetPos().x << "," << mySpace.GetPos().y
                      << ")\n";
        }
        HandleCollisionWithMap(maybeCollision.value());

        if (fromGravity) {
            std::cout << "[CheckCollisionWithMap-fromGravity]:Collision d\n";
            std::cout << "**** My pos: (" << mySpace.GetPos().x << "," << mySpace.GetPos().y
                      << ")\n";
        }
    } else {
        if (fromGravity) {
            std::cout << "[CheckCollisionWithMap-fromGravity]:NO collision\n";
        }
    }
}


void DynamicObject::MarkAsDead() { isDead = true; }

bool DynamicObject::IsDead() { return isDead; }

const Transform& DynamicObject::GetTransform() const { return mySpace; }
