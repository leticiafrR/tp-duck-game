#ifndef MOTION_HANDLER_H
#define MOTION_HANDLER_H
#include <vector>

#include "common/RigidBody.h"
#include "common/Vector2D.h"

class MotionHandler {
private:
    const int right;
    const int left;
    bool canJump;
    std::vector<bool> activeMoves;

public:
    MotionHandler(): right(1), left(0), canJump(true), activeMoves({false, false}) {}

    bool IsMovingRight() { return activeMoves[right]; }
    bool IsMovingLeft() { return activeMoves[left]; }

    void StartMoveRight(Vector2D& velocity, int speedX) {
        // std::cout << "[motion]: se agrega velocidad a la derecha\n";
        activeMoves[right] = true;
        velocity += (Vector2D::Right() * speedX);
    }

    void StartMoveLeft(Vector2D& velocity, int speedX) {
        // std::cout << "[motion]: se agrega velocidad a la izquierda\n";
        activeMoves[left] = true;
        velocity += (Vector2D::Left() * speedX);
    }

    void StopMoveLeft(Vector2D& velocity, int speedX) {
        if (IsMovingLeft()) {
            activeMoves[left] = false;
            velocity += (Vector2D::Left() * speedX * (-1));
        }
    }
    void StopMoveRight(Vector2D& velocity, int speedX) {
        // std::cout << "se llama a dejar de mover derecha\n";
        if (IsMovingRight()) {

            activeMoves[right] = false;
            velocity += (Vector2D::Right() * speedX * (-1));
        }
    }

    void CanJump(RigidBody& body) {
        canJump = true;
        body.ResetGravity();
        std::cout << "[MOTION]: terminaste de saltar, tienes velocidad: " << body.GetVelocity().x
                  << "," << body.GetVelocity().y << "\n";
        // std::cout << "[MOTION]: terminaste de saltar, tienes pos:
        // "<<body.<<","<<body.GetVelocity().y<<"\n";
    }

    void StartJump(RigidBody& body) {
        if (canJump) {
            canJump = false;
            std::cout << "[MOTION]: Acabas de saltar se bloquea la capacidad de jump, tienes "
                         "velocidad: "
                      << body.GetVelocity().x << "," << body.GetVelocity().y << "\n";
            body.ApplyForce(Vector2D::Up() * 75);

        } else {
            std::cout << "[MOTION] :)))))) se intentò saltar pero ya se habia saltado sin "
                         "reiniciar el canJump\n";
        }
    }
};

#endif
