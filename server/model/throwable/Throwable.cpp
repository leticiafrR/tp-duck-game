#include "Throwable.h"

#include "common/Collision.h"
#include "server/model/map/staticMap.h"
#define THROWABLE_SIZE 1
#define COEFFICIENT_FRICTION_AIR 15

Throwable::Throwable(float mass):
        DynamicObject(Transform(Vector2D::Zero(), Vector2D(THROWABLE_SIZE, THROWABLE_SIZE))),
        body(mySpace, mass, COEFFICIENT_FRICTION_AIR),
        isGrounded(false),
        beenThrown(false) {}


Vector2D Throwable::GetForceToBeThrown(const Vector2D& direction) {
    if (!direction.IsFarFrom(Vector2D::Up())) {
        return Vector2D::Up() * 30;
    }
    return (((direction) + Vector2D::Up()) * 20);
}

void Throwable::ApplyGravity(const StaticMap& map, float deltaTime) {
    body.Update(deltaTime);
    isGrounded = map.IsOnTheFloor(mySpace);
    if (isGrounded) {
        body.ResetGravity();
        CheckCollisionWithMap(map);
    }
}

void Throwable::BeThrown(const Vector2D& origin, const Vector2D& direction) {
    mySpace.SetPos(origin);
    body.ApplyForce(GetForceToBeThrown(direction));
    beenThrown = true;
    std::cout << "[THROW]: se lanzò con fuerza " << GetForceToBeThrown(direction).ToString()
              << std::endl;
}

void Throwable::Update(const StaticMap& map, float deltaTime) {
    if (beenThrown) {
        UpdatePosition(map, deltaTime);
        std::cout << "[Thowable]: updated pos is " << mySpace.GetPos().ToString() << std::endl;
    }
}
void Throwable::FollowPosition(const Vector2D& duckPos) { mySpace.SetPos(duckPos); }

void Throwable::HandleOutOfBounds(float /* disp*/) { MarkAsDead(); }

void Throwable::HandleCollisionWithMap(const Transform& mapT) {
    Collision::ResolveStaticCollision(mySpace, mapT);
}

ThrowableSpawnEventDto Throwable::GetMovingEventDto() {
    return ThrowableSpawnEventDto(GetTypeCollectable(), mySpace.GetPos());
}
