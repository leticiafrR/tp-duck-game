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
    RigidBody(Transform& transform, float mass);
    ~RigidBody();

    Vector2D GetVelocity() const;

    // Reset gravity should be called once it's sure that the object is grounded
    void ResetGravity();

    void ApplyForce(Vector2D force);

    void Update(float deltaTime);
};

#endif
