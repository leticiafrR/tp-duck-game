#ifndef MOTION_HANDLER_H
#define MOTION_HANDLER_H
#include <vector>

#include "common/Vector2D.h"
class MotionHandler {
private:
    const int right;
    const int left;
    std::vector<bool> activeMoves;

public:
    MotionHandler(): right(1), left(0), activeMoves({false, false}) {}

    bool IsMovingRight() { return activeMoves[right]; }
    bool IsMovingLeft() { return activeMoves[left]; }

    void StartMoveRight(Vector2D& velocity, int speedX) {
        activeMoves[right] = true;
        velocity += (Vector2D::Right() * speedX);
    }

    void StartMoveLeft(Vector2D& velocity, int speedX) {
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
        if (IsMovingRight()) {
            activeMoves[right] = false;
            velocity += (Vector2D::Right() * speedX * (-1));
        }
    }
};

#endif
