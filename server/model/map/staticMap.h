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
    std::string theme;
    std::vector<size_t> size;
    std::vector<float> limits;
    std::vector<GroundDto> grounds;
    std::vector<Vector2D> playersSpawnPlaces;
    std::vector<Vector2D> weaponsSpawnPoints;

    // void AddTransform(const Transform& obj);
    void AddGround(const GroundDto& grd);

    void SetTheLevel(const std::string& filePath);
    void loadPlatforms(const YAML::Node& config, const std::string& platformName);

public:
    explicit StaticMap(const std::string& lvlName);
    std::optional<float> DisplacementOutOfBounds(const Transform& dynamicT) const;

    bool IsOnTheFloor(const Transform& dynamicT) const;

    std::optional<std::pair<float, bool>> CheckCollisionRay(const Vector2D& rayOrigin,
                                                            const Vector2D& rayDirection,
                                                            float rayLenght) const;


    std::optional<Transform> CheckCollision(const Transform& dynamicT) const;

    std::vector<Vector2D> GetPlayersSpawnPoints();

    std::vector<Vector2D> GetWeaponsSpawnPoints();

    GameSceneDto GetScene();
    ~StaticMap() {}
};

#endif
