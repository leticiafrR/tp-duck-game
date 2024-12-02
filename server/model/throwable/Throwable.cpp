#include "Throwable.h"

#include "common/Collision.h"
#include "server/model/map/staticMap.h"

#define THROWABLE_SIZE 1
#define COEFFICIENT_FRICTION_AIR 15
#define THROWING_INTESITY 20
#define VERTICAL_THROWING_INTESITY 35
#define OFFSET_FROM_THROWER 2


Throwable::Throwable(float mass, TypeItem type):
        DynamicObject(Transform(Vector2D::Zero(), Vector2D(THROWABLE_SIZE, THROWABLE_SIZE))),
        type(type),
        body(mySpace, mass, COEFFICIENT_FRICTION_AIR),
        isGrounded(false),
        beenThrowed(false) {}


Vector2D Throwable::GetForceToBeThrown(const Vector2D& direction) {
    if (!direction.IsFarFrom(Vector2D::Up())) {
        return Vector2D::Up() * VERTICAL_THROWING_INTESITY;
    }
    return ((direction + Vector2D::Up()) * THROWING_INTESITY);
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
    beenThrowed = true;
    mySpace.SetPos(origin);
    body.ApplyForce(GetForceToBeThrown(direction));
}

void Throwable::Update(const StaticMap& map, float deltaTime) {
    if (beenThrowed) {
        UpdatePosition(map, deltaTime);
    }
}
void Throwable::FollowPosition(const Vector2D& duckPos) {
    mySpace.SetPos(duckPos + (Vector2D::Right() * OFFSET_FROM_THROWER));
}

void Throwable::HandleOutOfBounds(float /* displacement*/) { MarkAsDead(); }

void Throwable::HandleCollisionWithMap(const Transform& mapT) {
    Collision::ResolveStaticCollision(mySpace, mapT);
}

ThrowableSpawnEventDto Throwable::GetMovingEventDto() const {
    return ThrowableSpawnEventDto(type, mySpace.GetPos());
}
