#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector2D.h"

class Transform {
private:
    Vector2D position;
    Vector2D size;
    float angle;

public:
    Transform(Vector2D position = Vector2D::Zero(), Vector2D size = Vector2D::Zero(),
              float angle = 0) {
        SetPos(position);
        SetSize(size);
        SetAngle(angle);
    }

    void SetPos(Vector2D pos);
    void SetSize(Vector2D size);
    void SetAngle(float angle);

    void Move(Vector2D add);
    void Rotate(float add);

    Vector2D GetPos() const { return this->position; }
    Vector2D GetSize() const { return this->size; }
    float GetAngle() const { return this->angle; }

    Vector2D Min() const { return position - size / 2; }
    Vector2D Max() const { return position + size / 2; }

    ~Transform() = default;
};

void Transform::SetPos(Vector2D pos) { this->position = pos; }
void Transform::SetAngle(float angle) { this->angle = angle; }
void Transform::SetSize(Vector2D size) { this->size = size; }

void Transform::Move(Vector2D add) { this->position += add; }
void Transform::Rotate(float add) { this->angle += add; }

#endif
