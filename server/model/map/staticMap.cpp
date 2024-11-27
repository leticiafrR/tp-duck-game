#include "staticMap.h"

#include <algorithm>
#include <cmath>
#include <set>

#include <yaml-cpp/yaml.h>

#include "server/constantServer.h"

#include "constants.h"
enum : int { L, R, B, T };

// void StaticMap::AddTransform(const Transform& obj) { plataforms.emplace_back(obj); }

std::vector<Vector2D> StaticMap::GetPlayersSpawnPoints() { return playersSpawnPlaces; }

GameSceneDto StaticMap::GetScene() { return GameSceneDto(theme, plataforms, grounds); }

void StaticMap::AddGround(const GroundDto& grd) { grounds.emplace_back(grd); }


StaticMap::StaticMap(const std::string& fileName) { SetTheLevel(fileName); }


std::optional<std::pair<float, bool>> StaticMap::CheckCollisionRay(const Vector2D& rayOrigin,
                                                                   const Vector2D& rayDirection,
                                                                   float rayLenght) const {

    auto min_it = std::min_element(
            grounds.begin(), grounds.end(),
            [&rayDirection, &rayOrigin, rayLenght](const GroundDto& a, const GroundDto& b) {
                return Collision::RaycastDistanceAndDirection(rayOrigin, rayDirection, rayLenght,
                                                              a.mySpace)
                               .first < Collision::RaycastDistanceAndDirection(
                                                rayOrigin, rayDirection, rayLenght, b.mySpace)
                                                .first;
            });

    if (min_it != grounds.end()) {
        std::pair<float, bool> infoRay = Collision::RaycastDistanceAndDirection(
                rayOrigin, rayDirection, rayLenght, min_it->mySpace);
        return ((infoRay.first == rayLenght) ? std::nullopt :
                                               std::optional<std::pair<float, bool>>(infoRay));
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
                bool left = Collision::Raycast(posLeft, dir, len + 0.15f, ground.mySpace);
                bool right = Collision::Raycast(posRight, dir, len + 0.15f, ground.mySpace);
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

    float x = 0, y = 0, w = 0, h = 0;
    for (auto fl: plats) {
        std::string key = fl.first.as<std::string>();
        auto value = fl.second;
        if (key == X_STR) {
            x = value.as<float>();
        } else if (key == Y_STR) {
            y = value.as<float>();
        } else if (key == WEIGHT_STR) {
            w = value.as<float>();
        } else if (key == HIGH_STR) {
            h = value.as<float>();
        }
    }
    std::set<VISIBLE_EDGES> edges;
    for (auto edge: plats[EDGES_STR]) {
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


void StaticMap::SetTheLevel(const std::string& lvelName) {
    YAML::Node config = YAML::LoadFile(RELATIVE_LEVEL_PATH + lvelName + YAML_FILE);
    theme = config[THEME_STR].as<std::string>();
    size_t xSize = config[FULL_MAP_STR][X_STR].as<size_t>();
    size.emplace_back(xSize);
    size_t ySize = config[FULL_MAP_STR][Y_STR].as<size_t>();
    size.emplace_back(ySize);
    limits.emplace_back(-static_cast<int>(xSize) / HALF);  // izquierda [0]
    limits.emplace_back(xSize / HALF);                     // derecha [1]
    limits.emplace_back(-static_cast<int>(ySize) / HALF);  // inferior [2]
    limits.emplace_back(ySize / HALF);                     // superior [3]

    auto spawnPoints = config[PLAYERS_POINTS_STR];
    for (std::size_t i = 0; i < spawnPoints.size(); ++i) {
        Vector2D pos;
        pos.x = spawnPoints[i][X_STR].as<float>();
        pos.y = spawnPoints[i][Y_STR].as<float>();
        playersSpawnPlaces.push_back(pos);
    }

    auto _weaponsSpawnPoints = config[WEAPONS_POINTS_STR];
    for (std::size_t i = 0; i < _weaponsSpawnPoints.size(); ++i) {
        Vector2D pos;
        pos.x = _weaponsSpawnPoints[i][X_STR].as<float>();
        pos.y = _weaponsSpawnPoints[i][Y_STR].as<float>();
        weaponsSpawnPoints.push_back(pos);
    }

    auto platformsList = config[PLATFORMS_STR];
    for (std::size_t i = 0; i < platformsList.size(); ++i) {
        std::string platformName = platformsList[i].as<std::string>();
        loadPlatforms(config, platformName);
    }
}

std::vector<Vector2D> StaticMap::GetWeaponsSpawnPoints() { return weaponsSpawnPoints; }
