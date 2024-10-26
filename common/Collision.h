#ifndef COLLISION_H
#define COLLISION_H

#include <algorithm>

#include "Transform.h"

class Collision {
private:
public:
    static bool RectCollision(const Transform& a, const Transform& b) {
        Vector2D aPos = a.GetPos();
        Vector2D aSize = a.GetSize();
        Vector2D bPos = b.GetPos();
        Vector2D bSize = b.GetSize();
        return (aPos.x - (aSize.x / 2) < bPos.x + (bSize.x / 2) &&
                aPos.x + (aSize.x / 2) > bPos.x - (bSize.x) / 2 &&
                aPos.y - (aSize.y / 2) < bPos.y + (bSize.y / 2) &&
                aPos.y + (aSize.y / 2) > bPos.y - (bSize.y / 2));
    }

    static void ResolveStaticCollision(Transform& dynamicT, const Transform& staticT) {
        Vector2D dMax = dynamicT.GetPos() + dynamicT.GetSize() / 2;
        Vector2D dMin = dynamicT.GetPos() - dynamicT.GetSize() / 2;
        Vector2D sMax = staticT.GetPos() + staticT.GetSize() / 2;
        Vector2D sMin = staticT.GetPos() - staticT.GetSize() / 2;

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
