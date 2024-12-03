#ifndef MOTION_HANDLER_H
#define MOTION_HANDLER_H
#include <vector>

#include "common/Vector2D.h"
class MotionHandler {
private:
    bool movingToLeft;
    bool movingToRight;

public:
    MotionHandler();
    void StartMoveRight(Vector2D& velocity, int speedX);
    void StartMoveLeft(Vector2D& velocity, int speedX);
    void StopMoveLeft(Vector2D& velocity, int speedX);
    void StopMoveRight(Vector2D& velocity, int speedX);
};

#endif
