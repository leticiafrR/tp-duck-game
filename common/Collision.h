#ifndef COLLISION_H
#define COLLISION_H

#include <algorithm>
#include <cmath>
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


    static float LateralRaycastDistance(const Vector2D& rayOrigin, const Vector2D& rayDirection,
                                        float rayLenght, const Transform& candidateT) {
        Vector2D candidateApothem = (candidateT.GetSize() * 0.5f);

        float maxHeightCandidate = candidateT.GetPos().y + candidateApothem.y;
        float minHeighCandidate = candidateT.GetPos().y - candidateApothem.y;

        if (!(rayOrigin.y < maxHeightCandidate && minHeighCandidate < rayOrigin.y)) {
            return INFINITY;
        }

        float candidateSideX =
                candidateT.GetPos().x + ((rayDirection.x) * (-1) * candidateApothem.x);
        float rayEndX = rayOrigin.x + (rayDirection.x * rayLenght);

        if (!((rayOrigin.x < candidateSideX && candidateSideX < rayEndX) ||
              (rayEndX < candidateSideX && candidateSideX < rayOrigin.x))) {
            return INFINITY;
        }

        return (candidateSideX - rayOrigin.x) * rayDirection.x;
    }

    static float RaycastDistance(const Vector2D& rayOrigin, const Vector2D& rayDirection,
                                 float rayLenght, const Transform& candidateT) {

        Vector2D maxLimitisCandidate = candidateT.GetPos() + candidateT.GetSize() * 0.5f;
        Vector2D minLimitisCandidate = candidateT.GetPos() - candidateT.GetSize() * 0.5f;

        Vector2D rayEnd = rayOrigin + (rayDirection * rayLenght);
        Vector2D candidateSides;

        candidateSides.x = ((rayDirection.x > 0) ? minLimitisCandidate.x : maxLimitisCandidate.x);
        candidateSides.y = ((rayDirection.y > 0) ? minLimitisCandidate.y : maxLimitisCandidate.y);

        bool possibleCollisionX =
                ((rayDirection.x > 0) ?
                         ((rayOrigin.x < candidateSides.x) && (rayEnd.x > candidateSides.x)) :
                         (((rayDirection.x != 0) && rayOrigin.x > candidateSides.x) &&
                          (rayEnd.x < candidateSides.x)));
        bool possibleCollisionY =
                ((rayDirection.y > 0) ?
                         ((rayOrigin.y < candidateSides.y) && (rayEnd.y > candidateSides.y)) :
                         (((rayDirection.y != 0) && rayOrigin.y > candidateSides.y) &&
                          (rayEnd.y < candidateSides.y)));

        Vector2D rayEndByX = rayEnd;
        Vector2D rayEndByY = rayEnd;

        if (possibleCollisionX) {
            rayEndByX.x = candidateSides.x;
            rayEndByX.y = rayOrigin.y +
                          (rayDirection.y * ((candidateSides.x - rayOrigin.x) / rayDirection.x));

            if (!(minLimitisCandidate.y < rayEndByX.y && rayEndByX.y < maxLimitisCandidate.y)) {
                rayEndByX = rayOrigin + (rayDirection * rayLenght);
            }
        }

        if (possibleCollisionY) {
            rayEndByY.y = candidateSides.y;
            rayEndByY.x = rayOrigin.x +
                          (rayDirection.x * ((candidateSides.y - rayOrigin.y) / rayDirection.y));

            if (!(minLimitisCandidate.x < rayEndByY.x && rayEndByY.x < maxLimitisCandidate.x)) {
                rayEndByY = rayOrigin + (rayDirection * rayLenght);
            }
        }

        float minRayLenght = std::min((rayEndByX - rayOrigin).GetMagnitude(),
                                      (rayEndByY - rayOrigin).GetMagnitude());
        return minRayLenght;
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
                dynamicT.Move(Vector2D::Right() * (overlapX + 0.05f));  // Move right
            } else {
                dynamicT.Move(Vector2D::Left() * (overlapX + 0.05f));  // Move left
            }
        } else {
            if (dMin.y >= sMin.y) {
                dynamicT.Move(Vector2D::Up() * (overlapY + 0.05f));  // Move up
            } else {
                dynamicT.Move(Vector2D::Down() * (overlapY + 0.05f));  // Move down
            }
        }
    }

    Collision() = delete;
    ~Collision() = delete;
};

#endif
