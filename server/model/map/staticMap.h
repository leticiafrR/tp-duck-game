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

#include "common/Collision.h"
#include "common/Transform.h"
#include "data/gameScene.h"

class StaticMap {
private:
    std::string theme;
    std::vector<size_t> size;
    std::vector<float> limits;
    std::vector<Transform> plataforms;
    std::vector<GroundDto> grounds;
    std::vector<Vector2D> playersSpawnPlaces;
    void AddTransform(const Transform& obj);
    void AddGround(const GroundDto& grd);

    void AddEasyLevel();
    void AddTestLevel();
    void InitialMap();

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
