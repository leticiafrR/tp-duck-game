#ifndef STATICMAP_H
#define STATICMAP_H

#include <algorithm>
#include <iostream>
#include <list>
#include <optional>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "common/Collision.h"
#include "common/Transform.h"
#include "data/gameScene.h"

class StaticMap {
private:
    // cppcheck-suppress unusedStructMember
    std::string theme;
    // cppcheck-suppress unusedStructMember
    std::vector<size_t> size;
    // cppcheck-suppress unusedStructMember
    std::vector<float> limits;
    // cppcheck-suppress unusedStructMember
    std::vector<Transform> plataforms;
    // cppcheck-suppress unusedStructMember
    std::vector<GroundDto> grounds;
    // cppcheck-suppress unusedStructMember
    std::vector<Vector2D> playersSpawnPlaces;
    // cppcheck-suppress unusedPrivateFunction
    void AddTransform(const Transform& obj);
    void AddGround(const GroundDto& grd);

    void SetTheLevel(const std::string& filePath);
    void loadPlatforms(const YAML::Node& config, const std::string& platformName);

public:
    StaticMap();
    std::optional<float> DisplacementOutOfBounds(const Transform& dynamicT);

    bool IsOnTheFloor(const Transform& dynamicT);

    // retorna el nuevo largo para que colisione correctamente
    std::optional<float> CheckCollisionLateralRay(const Vector2D& rayOrigin,
                                                  const Vector2D& rayDirection,
                                                  float rayLenght) const;

    std::optional<Transform> CheckCollision(const Transform& dynamicT);

    std::vector<Vector2D> GetPlayersSpawnPoints();

    GameSceneDto GetScene();
    ~StaticMap() {}
};

#endif
