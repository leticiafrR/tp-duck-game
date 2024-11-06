#ifndef VECTOR_2D_H
#define VECTOR_2D_H
#include <cmath>

class Vector2D {
private:
public:
    static float Distance(Vector2D a, Vector2D b) { return (a - b).GetMagnitude(); }

    static Vector2D Zero() { return Vector2D(0, 0); }

    static Vector2D Right() { return Vector2D(1, 0); }
    static Vector2D Left() { return Vector2D(-1, 0); }
    static Vector2D Up() { return Vector2D(0, 1); }
    static Vector2D Down() { return Vector2D(0, -1); }

    // Lineal Interpolation
    static Vector2D Lerp(const Vector2D& start, const Vector2D& end, float t) {
        t = std::clamp(t, 0.0f, 1.0f);
        return start + (end - start) * t;
    }

    float x;
    float y;
    Vector2D(float x, float y) {
        this->x = x;
        this->y = y;
    }
    Vector2D() {
        x = 0;
        y = 0;
    }

    ~Vector2D() = default;

    bool IsFarFrom(const Vector2D& other, float tolerance = 0.001) const {
        return Distance(*this, other) > tolerance;
    }

    float GetMagnitude() { return std::sqrt(std::pow(x, 2) + std::pow(y, 2)); }

    Vector2D Normalized() {
        float magnitude = GetMagnitude();
        return Vector2D(x / magnitude, y / magnitude);
    }

    Vector2D& operator+=(const Vector2D& other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    Vector2D& operator*=(const float& other) {
        this->x *= other;
        this->y *= other;
        return *this;
    }

    Vector2D operator*(const float& other) const {
        return Vector2D(this->x * other, this->y * other);
    }
    Vector2D operator/(const float& other) const {
        return Vector2D(this->x / other, this->y / other);
    }

    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(this->x + other.x, this->y + other.y);
    }
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(this->x - other.x, this->y - other.y);
    }
};

#endif
