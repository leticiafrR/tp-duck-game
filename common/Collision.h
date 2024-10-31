#ifndef COLLISION_H
#define COLLISION_H

#include <algorithm>
#include <utility>

#include "Transform.h"

class Collision {
private:
public:
    static bool Raycast(const Vector2D& origin, const Vector2D& direction, float length,
                        const Transform& candidateT) {
        if (direction.x == 0 && direction.y == 0)  // Cant divide
            return false;

        // X Limits
        float tminX = (candidateT.Min().x - origin.x) / direction.x;
        float tmaxX = (candidateT.Max().x - origin.x) / direction.x;

        if (tminX > tmaxX)
            std::swap(tminX, tmaxX);

        // Y Limits
        float tminY = (candidateT.Min().y - origin.y) / direction.y;
        float tmaxY = (candidateT.Max().y - origin.y) / direction.y;

        if (tminY > tmaxY)
            std::swap(tminY, tmaxY);

        // Check intersection
        if (tminX > tmaxY || tminY > tmaxX)
            return false;

        // Hit range
        float tHit = std::max(tminX, tminY);

        // The hit is in range of lenght?
        return (tHit >= 0 && tHit <= length);
    }

    static bool RectCollision(const Transform& a, const Transform& b) {
        Vector2D aMax = a.Max();
        Vector2D aMin = a.Min();
        Vector2D bMax = b.Max();
        Vector2D bMin = b.Min();

        float overlapX = std::min(aMax.x, bMax.x) - std::max(aMin.x, bMin.x);
        float overlapY = std::min(aMax.y, bMax.y) - std::max(aMin.y, bMin.y);

        return (overlapX > 0) && (overlapY > 0);
    }

    static void ResolveStaticCollision(Transform& dynamicT, const Transform& staticT) {
        Vector2D dMax = dynamicT.Max();
        Vector2D dMin = dynamicT.Min();
        Vector2D sMax = staticT.Max();
        Vector2D sMin = staticT.Min();

        float overlapX = std::min(dMax.x, sMax.x) - std::max(dMin.x, sMin.x);
        float overlapY = std::min(dMax.y, sMax.y) - std::max(dMin.y, sMin.y);

        if (overlapX <= 0 || overlapY <= 0)
            return;

        if (overlapX < overlapY) {
            if (dMin.x > sMin.x) {
                dynamicT.Move(Vector2D::Right() * overlapX);  // Move right
            } else {
                dynamicT.Move(Vector2D::Left() * overlapX);  // Move left
            }
        } else {
            if (dMin.y > sMin.y) {
                dynamicT.Move(Vector2D::Up() * overlapY);  // Move up
            } else {
                dynamicT.Move(Vector2D::Down() * overlapY);  // Move down
            }
        }
    }

    Collision() = delete;
    ~Collision() = delete;
};

#endif
