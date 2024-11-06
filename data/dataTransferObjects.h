#ifndef DTO_H
#define DTO_H

#include <algorithm>
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

// no comunicar el valor de los angulos
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

/******************************GAME UPDATING DATA************************************/

struct DuckUpdate {
    typedef enum: uint8_t { RIGHT, LEFT, UP } FLIP;
    typedef enum: uint8_t { IDLE = 1, JUMP, FALLING, RUNNING, DEAD } DUCK_STATUS;
    Vector2D position;
    DUCK_STATUS status;
    FLIP flip;
};

struct Snapshot {
    bool gameEnded;
    // skiping the part  of making a player quit out of the game
    // std::vector<PlayerID_t> quiters;
    std::unordered_map<PlayerID_t, DuckUpdate> ducksUpdate;

    // cppcheck-suppress passedByValue
    Snapshot(bool gameEnded, std::unordered_map<PlayerID_t, DuckUpdate> ducksUpdate):
            gameEnded(gameEnded), ducksUpdate(ducksUpdate) {}
};

struct Command {
    typedef enum: uint8_t {
        LEFT_KEY_DOWN = 1,
        LEFT_KEY_UP,
        RIGHT_KEY_DOWN,
        RIGHT_KEY_UP,
        JUMP,
        QUIT
    } COMMAND_ID;

    uint8_t commandID;
    uint32_t playerID;

    explicit Command(uint8_t commandID, u_int32_t playerID = 0):
            commandID(commandID), playerID(playerID) {}
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
