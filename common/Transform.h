#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <string>

#include "Vector2D.h"

class Transform {
private:
    Vector2D position;
    Vector2D size;
    float angle;

public:
    explicit Transform(Vector2D position = Vector2D::Zero(), Vector2D size = Vector2D::Zero(),
                       float angle = 0);

    ~Transform();

    void SetPos(Vector2D pos);
    void SetSize(Vector2D size);
    void SetAngle(float angle);
    void Move(Vector2D add);
    void Rotate(float add);

    Vector2D GetPos() const;
    Vector2D GetSize() const;
    float GetAngle() const;

    Vector2D Min() const;
    Vector2D Max() const;

    void LookAt(Vector2D target, Vector2D worldUp = Vector2D::Right(), float offset = 0);

    std::string ToString();
};

#endif
