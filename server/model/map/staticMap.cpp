#include "staticMap.h"

#include <algorithm>
#include <cmath>

#include "mapConstants.h"
enum : int { L, R, B, T };


void StaticMap::AddTransform(const Transform& obj) { plataforms.emplace_back(obj); }

std::vector<Vector2D> StaticMap::GetPlayersSpawnPoints() { return playersSpawnPlaces; }

GameSceneDto StaticMap::GetScene() { return GameSceneDto(theme, plataforms, grounds); }

void StaticMap::AddGround(const GroundDto& grd) { grounds.emplace_back(grd); }


StaticMap::StaticMap(): theme(Theme::Forest) {
    size.emplace_back(FullMapSize::xMapSize);
    size.emplace_back(FullMapSize::yMapSize);
    limits.emplace_back(-static_cast<int>(FullMapSize::xMapSize) / 2);  // izquierda [0]
    limits.emplace_back(FullMapSize::xMapSize / 2);                     // derecha [1]
    limits.emplace_back(-static_cast<int>(FullMapSize::yMapSize) / 2);  // inferior [2]
    limits.emplace_back(FullMapSize::yMapSize / 2);                     // superior [3]
    AddEasyLevel();
}

std::optional<float> StaticMap::CheckCollisionLateralRay(const Vector2D& rayOrigin,
                                                         const Vector2D& rayDirection,
                                                         float rayLenght) const {
    auto min_it = std::min_element(
            grounds.begin(), grounds.end(),
            [&rayDirection, &rayOrigin, rayLenght](const GroundDto& a, const GroundDto& b) {
                return Collision::RaycastDistance(rayOrigin, rayDirection, rayLenght, a.mySpace) <
                       Collision::RaycastDistance(rayOrigin, rayDirection, rayLenght, b.mySpace);
            });

    if (min_it != grounds.end()) {
        float min_distance =
                Collision::RaycastDistance(rayOrigin, rayDirection, rayLenght, min_it->mySpace);
        return (std::isinf(min_distance)) ? std::nullopt : std::optional<float>(min_distance);
    }
    return std::nullopt;
}


bool StaticMap::IsOnTheFloor(const Transform& dynamicT) {
    Vector2D dir = Vector2D::Down();
    float len = (dynamicT.GetSize().y) / 2;
    float margen = (80 * len / 100);
    Vector2D posLeft(dynamicT.GetPos().x - margen, dynamicT.GetPos().y);
    Vector2D posRight(dynamicT.GetPos().x + margen, dynamicT.GetPos().y);

    return std::any_of(
            grounds.begin(), grounds.end(),
            [&dynamicT, &dir, len, posLeft, posRight](const auto& ground) {
                bool left = Collision::Raycast(posLeft, dir, len + 0.05f, ground.mySpace);
                bool right = Collision::Raycast(posRight, dir, len + 0.05f, ground.mySpace);
                return left || right;
            });
}


std::optional<float> StaticMap::DisplacementOutOfBounds(const Transform& dynamicT) {
    Vector2D posDynamic = dynamicT.GetPos();
    float xDynamic = posDynamic.x;
    float yDynamic = posDynamic.y;
    float radio = (dynamicT.GetSize().y) / 2;
    if (yDynamic - radio < limits[B]) {
        return -1;
    }
    if (xDynamic - radio < limits[L]) {
        return limits[L] - (xDynamic - radio);
    }
    if (yDynamic + radio > limits[T]) {
        return yDynamic + radio - limits[T];
    }
    if (xDynamic + radio > limits[R]) {
        return xDynamic + radio - limits[R];
    }
    return std::nullopt;  // El objeto está dentro de los límites
}

std::optional<Transform> StaticMap::CheckCollision(const Transform& dynamicT) {
    auto it = std::find_if(grounds.begin(), grounds.end(), [&dynamicT](const auto& ground) {
        return Collision::RectCollision(dynamicT, ground.mySpace);
    });
    if (it != grounds.end()) {
        return it->mySpace;
    }
    return std::nullopt;
}

void StaticMap::AddEasyLevel() {
    playersSpawnPlaces = PlayersSpawnPlaceEasyLevel::points;
    // plataforma 1
    Transform PlataformOne(Vector2D(PlataformOne::xPos, PlataformOne::yPos),
                           Vector2D(PlataformOne::xSize, PlataformOne::ySize));

    GroundDto GROne(PlataformOne, PlataformOne::edges);
    AddGround(GROne);
    // plataforma 2
    Transform PlataformTwo(Vector2D(PlataformTwo::xPos, PlataformTwo::yPos),
                           Vector2D(PlataformTwo::xSize, PlataformTwo::ySize));
    GroundDto GRTwo(PlataformTwo, PlataformTwo::edges);
    AddGround(GRTwo);

    // plataforma 3
    Transform PlataformThree(Vector2D(PlataformThree::xPos, PlataformThree::yPos),
                             Vector2D(PlataformThree::xSize, PlataformThree::ySize));
    GroundDto GRThree(PlataformThree, PlataformThree::edges);
    AddGround(GRThree);


    // plataforma 4
    Transform PlataformFour(Vector2D(PlataformFour::xPos, PlataformFour::yPos),
                            Vector2D(PlataformFour::xSize, PlataformFour::ySize));

    AddGround(GroundDto(PlataformFour, PlataformFour::edges));
    // plataforma 5
    Transform PlataformFive(Vector2D(PlataformFive::xPos, PlataformFive::yPos),
                            Vector2D(PlataformFive::xSize, PlataformFive::ySize));
    GroundDto GRFive(PlataformFive, PlataformFive::edges);
    AddGround(GRFive);
    // plataforma 6
    Transform PlataformSix(Vector2D(PlataformSix::xPos, PlataformSix::yPos),
                           Vector2D(PlataformSix::xSize, PlataformSix::ySize));
    GroundDto GRSix(PlataformSix, PlataformSix::edges);
    AddGround(GRSix);
    // plataforma 7
    Transform PlataformSeven(Vector2D(PlataformSeven::xPos, PlataformSeven::yPos),
                             Vector2D(PlataformSeven::xSize, PlataformSeven::ySize));
    GroundDto GRSeven(PlataformSeven, PlataformSeven::edges);
    AddGround(GRSeven);
    // plataforma 8
    Transform PlataformEight(Vector2D(PlataformEight::xPos, PlataformEight::yPos),
                             Vector2D(PlataformEight::xSize, PlataformEight::ySize));
    GroundDto GREight(PlataformEight, PlataformEight::edges);
    AddGround(GREight);
}
