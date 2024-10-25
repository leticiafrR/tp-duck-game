#ifndef COLLISION_H
#define COLLISION_H

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

    Collision() = delete;
    ~Collision() = delete;
};

#endif
