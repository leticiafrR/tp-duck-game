#include "MotionHandler.h"

#include "common/Vector2D.h"

MotionHandler::MotionHandler(): movingToLeft(false), movingToRight(false) {}
void MotionHandler::StartMoveRight(Vector2D& velocity, int speedX) {
    movingToRight = true;
    velocity += (Vector2D::Right() * speedX);
}

void MotionHandler::StartMoveLeft(Vector2D& velocity, int speedX) {
    movingToLeft = true;
    velocity += (Vector2D::Left() * speedX);
}

void MotionHandler::StopMoveLeft(Vector2D& velocity, int speedX) {
    if (movingToLeft) {
        movingToLeft = false;
        velocity += (Vector2D::Left() * speedX * (-1));
    }
}
void MotionHandler::StopMoveRight(Vector2D& velocity, int speedX) {
    if (movingToRight) {
        movingToRight = false;
        velocity += (Vector2D::Right() * speedX * (-1));
    }
}
