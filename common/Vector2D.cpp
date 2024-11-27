#include "Vector2D.h"

float Vector2D::Distance(Vector2D a, Vector2D b) { return (a - b).GetMagnitude(); }

Vector2D Vector2D::Zero() { return Vector2D(0, 0); }

Vector2D Vector2D::Right() { return Vector2D(1, 0); }
Vector2D Vector2D::Left() { return Vector2D(-1, 0); }
Vector2D Vector2D::Up() { return Vector2D(0, 1); }
Vector2D Vector2D::Down() { return Vector2D(0, -1); }

// Lineal Interpolation
Vector2D Vector2D::Lerp(const Vector2D& start, const Vector2D& end, float t) {
    t = std::clamp(t, 0.0f, 1.0f);
    return start + (end - start) * t;
}

Vector2D Vector2D::MoveTowards(const Vector2D& current, const Vector2D& target,
                               float maxDistanceDelta) {
    Vector2D dir = target - current;
    float dist = dir.GetMagnitude();

    if (dist <= maxDistanceDelta || dist == 0) {
        return target;
    } else {
        Vector2D normalizedDirection = dir.Normalized();
        return current + normalizedDirection * maxDistanceDelta;
    }
}

Vector2D Vector2D::GetOrthogonal(const Vector2D& v) { return Vector2D(-v.y, v.x); }

float Vector2D::DotProduct(Vector2D a, Vector2D b) { return a.x * b.x + a.y * b.y; }

float Vector2D::AngleBetween(Vector2D a, Vector2D b) {
    float magnitudeA = a.GetMagnitude();
    float magnitudeB = b.GetMagnitude();

    if (magnitudeA == 0 || magnitudeB == 0)
        return 0;

    float cos = DotProduct(a, b) / (magnitudeA * magnitudeB);
    cos = std::clamp(cos, -1.0f, 1.0f);

    return std::acos(cos) * 180.0f / M_PI;
}

Vector2D::Vector2D(float x, float y) {
    this->x = x;
    this->y = y;
}
Vector2D::Vector2D() {
    x = 0;
    y = 0;
}

Vector2D::~Vector2D() = default;

bool Vector2D::IsFarFrom(const Vector2D& other, float tolerance) const {
    return Distance(*this, other) > tolerance;
}

float Vector2D::GetMagnitude() const { return std::sqrt(std::pow(x, 2) + std::pow(y, 2)); }

Vector2D Vector2D::Normalized() const {
    float magnitude = GetMagnitude();
    if (magnitude == 0) {
        return Vector2D::Zero();
    }
    return Vector2D(x / magnitude, y / magnitude);
}

void Vector2D::Rotate(float angle) {
    float angleRadian = angle * M_PI / 180.0f;
    float oldX = x;
    float oldY = y;
    x = oldX * std::cos(angleRadian) - oldY * std::sin(angleRadian);
    y = oldX * std::sin(angleRadian) + oldY * std::cos(angleRadian);
}

Vector2D Vector2D::ReflectAcross(const Vector2D& axis) const {
    Vector2D normalizedAxis = axis.Normalized();
    float projectionOnAxis = DotProduct(*this, normalizedAxis);
    return (normalizedAxis * (2 * projectionOnAxis)) - *this;
}

std::string Vector2D::ToString() const {
    std::string xStr = (std::ostringstream() << std::fixed << std::setprecision(2) << x).str();
    std::string yStr = (std::ostringstream() << std::fixed << std::setprecision(2) << y).str();
    return "(" + xStr + ", " + yStr + ")";
}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Vector2D& Vector2D::operator*=(const float& other) {
    this->x *= other;
    this->y *= other;
    return *this;
}

Vector2D Vector2D::operator*(const float& other) const {
    return Vector2D(this->x * other, this->y * other);
}
Vector2D Vector2D::operator/(const float& other) const {
    return Vector2D(this->x / other, this->y / other);
}

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(this->x + other.x, this->y + other.y);
}
Vector2D Vector2D::operator-(const Vector2D& other) const {
    return Vector2D(this->x - other.x, this->y - other.y);
}
