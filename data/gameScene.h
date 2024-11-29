#ifndef GAME_SCENE_H
#define GAME_SCENE_H
#include <cstdint>
#include <set>
#include <string>
#include <vector>

#include "common/Transform.h"

#include "networkMsg.h"

typedef enum: uint8_t { RIGHT, LEFT, TOP, BOTTOM } VISIBLE_EDGES;

struct GroundDto {
    std::set<VISIBLE_EDGES> visibleEdges;
    Transform mySpace;

    GroundDto(const Transform& mySpace, const std::set<VISIBLE_EDGES>& visibleEdges):
            visibleEdges(visibleEdges), mySpace(mySpace) {}
    GroundDto() = default;
};

struct GameSceneDto: public NetworkMsg {
    std::string theme;
    std::vector<GroundDto> groundBlocks;

    GameSceneDto(const std::string& theme, const std::vector<GroundDto>& groundBlocks):
            theme(theme), groundBlocks(groundBlocks) {}
};

#endif
