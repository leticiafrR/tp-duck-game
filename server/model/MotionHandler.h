#ifndef MOTION_HANDLER_H
#define MOTION_HANDLER_H
#include <vector>

#include "common/Vector2D.h"
class MotionHandler {
private:
    bool movingToLeft = false;
    bool movingToRight = false;

public:
    void StartMoveRight(Vector2D& velocity, int speedX) {
        movingToRight = true;
        velocity += (Vector2D::Right() * speedX);
    }

    void StartMoveLeft(Vector2D& velocity, int speedX) {
        movingToLeft = true;
        velocity += (Vector2D::Left() * speedX);
    }

    void StopMoveLeft(Vector2D& velocity, int speedX) {
        if (movingToLeft) {
            movingToLeft = false;
            velocity += (Vector2D::Left() * speedX * (-1));
        }
    }
    void StopMoveRight(Vector2D& velocity, int speedX) {
        if (movingToRight) {
            movingToRight = false;
            velocity += (Vector2D::Right() * speedX * (-1));
        }
    }
};

#endif
