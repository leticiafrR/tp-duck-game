#include "Transform.h"

Transform::Transform(Vector2D position, Vector2D size, float angle) {
    SetPos(position);
    SetSize(size);
    SetAngle(angle);
}

Transform::~Transform() = default;

void Transform::SetPos(Vector2D pos) { this->position = pos; }
void Transform::SetSize(Vector2D size) { this->size = size; }
void Transform::SetAngle(float angle) { this->angle = angle; }
void Transform::Move(Vector2D add) { this->position += add; }
void Transform::Rotate(float add) { this->angle += add; }

Vector2D Transform::GetPos() const { return this->position; }
Vector2D Transform::GetSize() const { return this->size; }
float Transform::GetAngle() const { return this->angle; }

Vector2D Transform::Min() const { return position - size / 2; }
Vector2D Transform::Max() const { return position + size / 2; }

void Transform::LookAt(Vector2D target, Vector2D worldUp, float offset) {
    angle = Vector2D::AngleBetween((target - position), worldUp);
    angle += offset;
    if (target.y - position.y < 0)
        angle = 360.0 - angle;
}

std::string Transform::ToString() {
    return "Position: " + position.ToString() + " - Size: " + size.ToString();
}
