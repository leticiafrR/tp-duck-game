#include "staticMap.h"

#include <algorithm>
#include <cmath>
#include <set>

#include <yaml-cpp/yaml.h>

#include "server/constantServer.h"
enum : int { L, R, B, T };

const static char filePath[] = "../config/levels/level_1.yaml";

// void StaticMap::AddTransform(const Transform& obj) { plataforms.emplace_back(obj); }

std::vector<Vector2D> StaticMap::GetPlayersSpawnPoints() { return playersSpawnPlaces; }

GameSceneDto StaticMap::GetScene() { return GameSceneDto(theme, plataforms, grounds); }

void StaticMap::AddGround(const GroundDto& grd) { grounds.emplace_back(grd); }


StaticMap::StaticMap() { SetTheLevel(filePath); }

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
    float len = (dynamicT.GetSize().y) / HALF;
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
    float radio = (dynamicT.GetSize().y) / HALF;
    if (yDynamic - radio < limits[B]) {
        return FALLING;
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
void StaticMap::loadPlatforms(const YAML::Node& config, const std::string& platformName) {
    auto plats = config[platformName];
    for (std::size_t i = 0; i < plats.size(); ++i) {
        float x = plats[i][X_STR].as<float>();
        float y = plats[i][Y_STR].as<float>();
        float w = plats[i][WEIGHT_STR].as<float>();
        float h = plats[i][HIGH_STR].as<float>();

        std::set<VISIBLE_EDGES> edges;
        for (auto edge: plats[i][EDGES_STR]) {
            std::string edgeStr = edge.as<std::string>();
            if (edgeStr == LEFT_STR)
                edges.insert(LEFT);
            else if (edgeStr == RIGHT_STR)
                edges.insert(RIGHT);
            else if (edgeStr == TOP_STR)
                edges.insert(TOP);
            else if (edgeStr == BOTTOM_STR)
                edges.insert(BOTTOM);
        }
        AddGround(GroundDto(Transform(Vector2D(x, y), Vector2D(w, h), 0), edges));
    }
}

void StaticMap::SetTheLevel(const std::string& filePath) {
    YAML::Node config = YAML::LoadFile(filePath);
    theme = config[THEME_STR].as<std::string>();
    size_t xSize = config[FULL_MAP_STR][X_STR].as<size_t>();
    size.emplace_back(xSize);
    size_t ySize = config[FULL_MAP_STR][Y_STR].as<size_t>();
    size.emplace_back(ySize);
    limits.emplace_back(-static_cast<int>(xSize) / 2);  // izquierda [0]
    limits.emplace_back(xSize / 2);                     // derecha [1]
    limits.emplace_back(-static_cast<int>(ySize) / 2);  // inferior [2]
    limits.emplace_back(ySize / 2);                     // superior [3]

    auto spawnPoints = config[PLAYERS_POINTS_STR];
    for (std::size_t i = 0; i < spawnPoints.size(); ++i) {
        Vector2D pos;
        pos.x = spawnPoints[i][X_STR].as<float>();
        pos.y = spawnPoints[i][Y_STR].as<float>();
        playersSpawnPlaces.push_back(pos);
    }
    YAML::Node platformsList = config[PLATAFORM_STR][0];
    for (std::size_t i = 0; i < platformsList.size(); ++i) {
        std::string platformName = platformsList[i].as<std::string>();

        loadPlatforms(config, platformName);
    }
}
