#ifndef DTO_H
#define DTO_H

#include <algorithm>
#include <cstdint>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "../data/id.h"

#include "Transform.h"
#include "Vector2D.h"

/******************************MATCH STARTING DATA***********************************/
struct PlayerData {
    PlayerID_t playerID;
    uint8_t playerSkin;
    std::string nickname;

    PlayerData(PlayerID_t playerID, uint8_t playerSkin, const std::string& nickname):
            playerID(playerID), playerSkin(playerSkin), nickname(nickname) {}
};

struct MatchStartDto {
    std::vector<PlayerData> playersData;
    Vector2D duckSize;

    MatchStartDto(const std::vector<PlayerData>& playersData, Vector2D duckSize):
            playersData(playersData), duckSize(duckSize) {}
};

/******************************GAME STARTING DATA************************************/

struct GroundDto {
    typedef enum: uint8_t { RIGHT, LEFT, TOP, BOTTOM } VISIBLE_EDGES;
    std::set<VISIBLE_EDGES> visibleEdges;
    Transform transform;

    GroundDto(const Transform& transform, const std::set<VISIBLE_EDGES>& visibleEdges):
            transform(transform), visibleEdges(visibleEdges) {}
};

struct GameSceneDto {
    std::string theme;
    std::vector<Transform> platforms;
    std::vector<GroundDto> groundBlocks;

    GameSceneDto(const std::string& theme, const std::vector<Transform>& platforms,
                 const std::vector<GroundDto>& groundBlocks):
            theme(theme), platforms(platforms), groundBlocks(groundBlocks) {}
};

/******************************GROUP GAMES RECOUNT DATA******************************/

struct GamesRecountDto {
    bool matchEnded;
    std::unordered_map<PlayerID_t, int> results;

    GamesRecountDto(bool matchEnded, const std::unordered_map<PlayerID_t, int>& results):
            matchEnded(matchEnded), results(results) {}
};


#endif
