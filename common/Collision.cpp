#include "Collision.h"

bool Collision::Raycast(const Vector2D& origin, const Vector2D& direction, float length,
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

std::pair<float, bool> Collision::RaycastDistanceAndDirection(const Vector2D& rayOrigin,
                                                              const Vector2D& rayDirection,
                                                              float rayLenght,
                                                              const Transform& candidateT) {

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
    float distanceFromVertical = (rayEndByY - rayOrigin).GetMagnitude();
    float distanceFromHorizontal = (rayEndByX - rayOrigin).GetMagnitude();
    if (distanceFromVertical < distanceFromHorizontal) {
        return {distanceFromVertical, true};
    }
    return {distanceFromHorizontal, false};
}

bool Collision::RectCollision(const Transform& a, const Transform& b) {
    Vector2D aMax = a.Max();
    Vector2D aMin = a.Min();
    Vector2D bMax = b.Max();
    Vector2D bMin = b.Min();

    float overlapX = std::min(aMax.x, bMax.x) - std::max(aMin.x, bMin.x);
    float overlapY = std::min(aMax.y, bMax.y) - std::max(aMin.y, bMin.y);

    return (overlapX > 0) && (overlapY > 0);
}

void Collision::ResolveStaticCollision(Transform& dynamicT, const Transform& staticT) {
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
