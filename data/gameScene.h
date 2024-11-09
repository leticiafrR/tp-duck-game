#ifndef GAME_SCENE_H
#define GAME_SCENE_H
#include <cstdint>
#include <set>
#include <string>
#include <vector>

#include "common/Transform.h"

typedef enum: uint8_t { RIGHT, LEFT, TOP, BOTTOM } VISIBLE_EDGES;

struct GroundDto {
    std::set<VISIBLE_EDGES> visibleEdges;
    Transform mySpace;

    GroundDto(const Transform& mySpace, const std::set<VISIBLE_EDGES>& visibleEdges):
            visibleEdges(visibleEdges), mySpace(mySpace) {}
    GroundDto() = default;
};

struct GameSceneDto {
    std::string theme;
    std::vector<Transform> platforms;
    std::vector<GroundDto> groundBlocks;

    GameSceneDto(const std::string& theme, const std::vector<Transform>& platforms,
                 const std::vector<GroundDto>& groundBlocks):
            theme(theme), platforms(platforms), groundBlocks(groundBlocks) {}
};

#endif
