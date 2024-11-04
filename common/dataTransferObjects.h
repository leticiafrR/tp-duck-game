#ifndef DTO_H
#define DTO_H

#include <string>
#include <unordered_map>
#include <vector>

#include "../common/Transform.h"
#include "../common/Vector2D.h"
#include "../data/id.h"


struct MatchStartSettingsDto {
    std::vector<PlayerID_t> playerIDs;
    std::vector<std::string> playerNicknames;
    std::vector<int> playerSkins;
    Vector2D duckSize;

    MatchStartSettingsDto(int numberPlayers, Vector2D duckSize):
            playerIDs(numberPlayers),
            playerNicknames(numberPlayers),
            playerSkins(numberPlayers),
            duckSize(duckSize) {}
};

// no comunicar el valor de los angulos
struct GameStartSettingsDto {
    std::string theme;
    std::vector<Transform> platforms;
    // Maybe sould cointain a difference btwn the walls and the floor

    // cppcheck-suppress passedByValue
    GameStartSettingsDto(std::string theme, std::vector<Transform> platforms):
            theme(theme), platforms(platforms) {}
};

struct Snapshot {
    bool gameEnded;
    std::unordered_map<PlayerID_t, Vector2D> positionsUpdate;

    // cppcheck-suppress passedByValue
    Snapshot(bool gameEnded, std::unordered_map<PlayerID_t, Vector2D> positionsUpdate):
            gameEnded(gameEnded), positionsUpdate(positionsUpdate) {}
};

typedef enum: uint8_t { MOVEMENT = 1, CONTROL_MATCH_STATE } MESSAGE_TYPE;

// Note: the jump cmmd its not prolonged
typedef enum: uint8_t {
    LEFT_KEY_DOWN = 1,
    LEFT_KEY_UP,
    RIGHT_KEY_DOWN,
    RIGHT_KEY_UP,
    JUMP
} MOVEMENT_IDS;

typedef enum: uint8_t {
    QUIT_MATCH = 1
    //, CREATE_MATCH,JOIN_MMATCH, REFRESH
} CONTROL_MATCH_STATE;

struct Command {
    uint8_t commandType;
    uint8_t commandID;
    uint32_t playerID;

    Command(uint8_t commandType, uint8_t commandID, u_int32_t playerID = 0):
            commandType(commandType), commandID(commandID), playerID(playerID) {}
};

struct GamesRecountDto {
    bool matchEnded;
    std::unordered_map<PlayerID_t, int> results;
    // cppcheck-suppress passedByValue
    GamesRecountDto(bool matchEnded, std::unordered_map<PlayerID_t, int> results):
            matchEnded(matchEnded), results(results) {}
};


#endif
