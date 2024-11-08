#ifndef GROUND_DTO_H
#define GROUND_DTO_H
#include <set>

#include "common/Transform.h"

typedef enum: uint8_t { RIGHT, LEFT, TOP, BOTTOM } VISIBLE_EDGES;

struct GroundDto {
    std::set<VISIBLE_EDGES> visibleEdges;
    Transform mySpace;

    GroundDto(const Transform& mySpace, const std::set<VISIBLE_EDGES>& visibleEdges):
            visibleEdges(visibleEdges), mySpace(mySpace) {}
    GroundDto() = default;
};

#endif
