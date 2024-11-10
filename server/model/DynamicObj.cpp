#include "DynamicObj.h"

#include "map/staticMap.h"
/*******************************************************************************************/
/*                                DEFINITIONS                                              */
/*******************************************************************************************/

DynamicObject::DynamicObject(int speedX, const Transform& mySpace):
        mySpace(mySpace), isDead(false), speedX(speedX) {}


void DynamicObject::UpdatePosition(StaticMap& map, float deltaTime) {
    mySpace.Move(velocity * deltaTime);
    // std::cout << "  [Dynamic]: after literraly moving:
    // "<<mySpace.GetPos().x<<","<<mySpace.GetPos().y<<")\n";
    CheckInteractionWithMap(map, deltaTime);
    // std::cout << "  [Dynamic]: after interacting with map:
    // "<<mySpace.GetPos().x<<","<<mySpace.GetPos().y<<")\n";
}

void DynamicObject::CheckInteractionWithMap(StaticMap& map, float deltaTime) {
    ApplyGravity(map, deltaTime);
    // std::cout << "      [Dynamic]: after gravity:
    // "<<mySpace.GetPos().x<<","<<mySpace.GetPos().y<<")\n";
    CheckOutOfMapBoundaries(map);
    // std::cout << "  [Dynamic]: after boundaries:
    // "<<mySpace.GetPos().x<<","<<mySpace.GetPos().y<<")\n";
    CheckCollisionWithMap(map);
    // std::cout << "  [Dynamic]: after collision:
    // "<<mySpace.GetPos().x<<","<<mySpace.GetPos().y<<")\n";
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
