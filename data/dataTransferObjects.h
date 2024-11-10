#ifndef DTO_H
#define DTO_H

#include <algorithm>
#include <cstdint>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "../data/id.h"
#include "common/Transform.h"
#include "common/Vector2D.h"

#include "networkMsg.h"

/******************************MATCH STARTING DATA***********************************/
struct PlayerData {
    PlayerID_t playerID;
    uint8_t playerSkin;
    std::string nickname;

    PlayerData(): playerID(0), playerSkin(0), nickname("") {}
    PlayerData(PlayerID_t playerID, uint8_t playerSkin, const std::string& nickname):
            playerID(playerID), playerSkin(playerSkin), nickname(nickname) {}
};

struct MatchStartDto: public NetworkMsg {
    std::vector<PlayerData> playersData;
    Vector2D duckSize;

    MatchStartDto(const std::vector<PlayerData>& playersData, Vector2D duckSize):
            playersData(playersData), duckSize(duckSize) {}
};

/******************************GROUP GAMES RECOUNT DATA******************************/

struct GamesRecountDto: public NetworkMsg {
    bool matchEnded;
    std::unordered_map<PlayerID_t, int> results;

    GamesRecountDto(bool matchEnded, const std::unordered_map<PlayerID_t, int>& results):
            matchEnded(matchEnded), results(results) {}
};


#endif
