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

    // cppcheck-suppress passedByValue
    PlayerData(PlayerID_t playerID, uint8_t playerSkin, std::string nickname):
            playerID(playerID), playerSkin(playerSkin), nickname(nickname) {}
};

struct MatchStartDto {
    std::vector<PlayerData> playersData;
    Vector2D duckSize;

    // cppcheck-suppress passedByValue
    MatchStartDto(std::vector<PlayerData> playersData, Vector2D duckSize):
            playersData(playersData), duckSize(duckSize) {}
};

/******************************GAME STARTING DATA************************************/

struct GroundDto {
    typedef enum: uint8_t { RIGHT, LEFT, TOP, BOTTOM } VISIBLE_EDGES;
    std::set<VISIBLE_EDGES> visibleEdges;
    Transform transform;

    // cppcheck-suppress passedByValue
    GroundDto(Transform transform, std::set<VISIBLE_EDGES> visibleEdges):
            transform(transform), visibleEdges(visibleEdges) {}
};

struct GameSceneDto {
    std::string theme;
    std::vector<Transform> platforms;
    std::vector<GroundDto> groundBlocks;

    //  cppcheck-suppress passedByValue
    GameSceneDto(std::string theme, std::vector<Transform> platforms,
                 // cppcheck-suppress passedByValue
                 std::vector<GroundDto> groundBlocks):
            theme(theme), platforms(platforms), groundBlocks(groundBlocks) {}
};

/******************************GROUP GAMES RECOUNT DATA******************************/

struct GamesRecountDto {
    bool matchEnded;
    std::unordered_map<PlayerID_t, int> results;
    // cppcheck-suppress passedByValue
    GamesRecountDto(bool matchEnded, std::unordered_map<PlayerID_t, int> results):
            matchEnded(matchEnded), results(results) {}
};


#endif
