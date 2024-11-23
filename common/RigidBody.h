#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include "Transform.h"

#define GRAVITY 9.81f

class RigidBody {
private:
    Transform& sourceT;
    Vector2D velocity;
    float mass;

public:
    RigidBody(Transform& transform, float mass): sourceT(transform), mass(mass) {}
    ~RigidBody() = default;

    Vector2D GetVelocity() const { return this->velocity; }

    // Reset gravity should be called once it's sure that the object is grounded
    void ResetGravity() { velocity.y = 0; }

    void ApplyForce(Vector2D force) { velocity += force; }

    void Update(float deltaTime) {
        Vector2D lastPos = sourceT.GetPos();

        ApplyForce(Vector2D::Down() * GRAVITY * mass * deltaTime);  // Gravity

        if (velocity.GetMagnitude() > 0)
            velocity.x += (velocity.Normalized() * -200 * deltaTime).x;  // Friction

        sourceT.Move(velocity * deltaTime);  // Movement update
    }
};

#endif
