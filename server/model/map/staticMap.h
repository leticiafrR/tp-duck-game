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
#include "common/Collision.h"
#include "common/Transform.h"

class StaticMap {
private:
    // cppcheck-suppress unusedStructMember
    [[clang::suppress_unused]] std::string theme;
    // cppcheck-suppress unusedStructMember
    [[clang::suppres_unused]] std::vector<size_t> size;
    // cppcheck-suppress unusedStructMember
    [[clang::suppres_unused]] std::vector<float> limits;
    // cppcheck-suppress unusedStructMember
    [[clang::suppres_unused]] std::vector<Transform> plataforms;
    // cppcheck-suppress unusedStructMember
    [[clang::suppres_unused]] std::vector<GroundDto> grounds;
    void AddTransform(const Transform& obj);
    void AddGround(const GroundDto& grd);

    void AddEasyLevel();
    void AddTestLevel();

public:
    StaticMap();  // recibira el nombre del archivo con el nivel a agregar
    // esta en el mapa
    std::optional<float> DisplacementOutOfBounds(const Transform& dynamicT);

    bool IsOnTheFloor(const Transform& dynamicT);
    std::optional<Transform> CheckCollision(const Transform& dynamicT);

    std::vector<Vector2D> GetPlayersSpawnPoints();

    GameSceneDto GetScene();
    ~StaticMap() {}
};
#endif
