#ifndef COLLISION_H
#define COLLISION_H

#include <algorithm>
#include <cmath>
#include <utility>

#include "Transform.h"

class Collision {
private:
    Collision() = delete;
    ~Collision() = delete;

public:
    static bool Raycast(const Vector2D& origin, const Vector2D& direction, float length,
                        const Transform& candidateT);

    // returns the distancce that the ray reaches and a boolean indicating if there is a vertical
    // collision with the candidate
    static std::pair<float, bool> RaycastDistanceAndDirection(const Vector2D& rayOrigin,
                                                              const Vector2D& rayDirection,
                                                              float rayLenght,
                                                              const Transform& candidateT);

    static bool RectCollision(const Transform& a, const Transform& b);

    static void ResolveStaticCollision(Transform& dynamicT, const Transform& staticT);
};

#endif
