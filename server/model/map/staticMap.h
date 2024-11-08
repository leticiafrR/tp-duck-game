#ifndef STATICMAP_H
#define STATICMAP_H

#include <algorithm>
#include <iostream>
#include <list>
#include <optional>
#include <random>
#include <string>
#include <vector>

#include "../../../data/groundDta.h"
#include "common/Transform.h"

class StaticMap {
private:
    std::vector<size_t> size;
    std::vector<float> limits;
    std::vector<Transform> plataforms;  // por ahora no le veo una ventaja a usar vector
    std::vector<GroundDto> grounds;
    void AddTransform(const Transform& obj);
    void AddGround(const GroundDto& grd);

public:
    StaticMap();
    std::optional<float> DisplacementOutOfBounds(const Transform& dynamicT);

    bool IsOnTheFloor(const Transform& dynamicT);

    std::optional<Transform> CheckCollision(const Transform& dynamicT);

    std::vector<Vector2D> GetPlayersSpawnPoints();
    std::vector<Transform> getPlataforms();
    std::vector<GroundDto> getGrounds();

    ~StaticMap() = default;
};
#endif
