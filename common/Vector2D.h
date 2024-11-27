#ifndef VECTOR_2D_H
#define VECTOR_2D_H
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

class Vector2D {
private:
public:
    static float Distance(Vector2D a, Vector2D b);
    static Vector2D Zero();

    static Vector2D Right();
    static Vector2D Left();
    static Vector2D Up();
    static Vector2D Down();

    // Lineal Interpolation
    static Vector2D Lerp(const Vector2D& start, const Vector2D& end, float t);

    static Vector2D MoveTowards(const Vector2D& current, const Vector2D& target,
                                float maxDistanceDelta);

    static Vector2D GetOrthogonal(const Vector2D& v);

    static float DotProduct(Vector2D a, Vector2D b);

    static float AngleBetween(Vector2D a, Vector2D b);

    float x;
    float y;

    Vector2D(float x, float y);
    Vector2D();

    ~Vector2D();

    bool IsFarFrom(const Vector2D& other, float tolerance = 0.001) const;

    float GetMagnitude() const;

    Vector2D Normalized() const;

    void Rotate(float angle);

    Vector2D ReflectAcross(const Vector2D& axis) const;

    std::string ToString() const;

    Vector2D& operator+=(const Vector2D& other);

    Vector2D& operator*=(const float& other);

    Vector2D operator*(const float& other) const;
    Vector2D operator/(const float& other) const;

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
};

#endif
