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
                       float angle = 0) {
        SetPos(position);
        SetSize(size);
        SetAngle(angle);
    }

    void SetPos(Vector2D pos) { this->position = pos; }
    void SetSize(Vector2D size) { this->size = size; }
    void SetAngle(float angle) { this->angle = angle; }
    void Move(Vector2D add) { this->position += add; }
    void Rotate(float add) { this->angle += add; }

    Vector2D GetPos() const { return this->position; }
    Vector2D GetSize() const { return this->size; }
    float GetAngle() const { return this->angle; }

    Vector2D Min() const { return position - size / 2; }
    Vector2D Max() const { return position + size / 2; }

    std::string ToString() {
        std::string fmt = "Position: (";
        fmt += std::to_string(position.x);
        fmt += ", ";
        fmt += std::to_string(position.y);
        fmt += ") - Size: (";
        fmt += std::to_string(size.x);
        fmt += ", ";
        fmt += std::to_string(size.y);
        fmt += ")";
        return fmt;
    }

    ~Transform() = default;
};

#endif
