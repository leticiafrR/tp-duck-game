#include "RigidBody.h"

RigidBody::RigidBody(Transform& transform, float mass, float coefficientFriction):
        sourceT(transform), mass(mass), coefficientFriction(coefficientFriction) {}
RigidBody::~RigidBody() = default;

Vector2D RigidBody::GetVelocity() const { return this->velocity; }

void RigidBody::ResetGravity() { velocity.y = 0; }

void RigidBody::ApplyForce(Vector2D force) { velocity += force; }

void RigidBody::Update(float deltaTime) {
    Vector2D lastPos = sourceT.GetPos();

    ApplyForce(Vector2D::Down() * GRAVITY * mass * deltaTime);  // Gravity

    if (velocity.GetMagnitude() > 0)
        velocity.x += (velocity.Normalized() * (-coefficientFriction) * deltaTime).x;  // Friction

    sourceT.Move(velocity * deltaTime);  // Movement update
}
