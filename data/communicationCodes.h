#ifndef COMMUNICATION_CODES_H
#define COMMUNICATION_CODES_H

#include <cstdint>

typedef enum: uint8_t {
    NICKNAME = 1,
    IDENTIFICATION,
    MATCH_SELECTION,
    AVAILABLE_MATCHES,
    RESULT_JOINING,
    START_MATCH_INTENTION,
    RESULT_STARTING,
    MATCH_STARTING_SETTINGS,
    GAME_SCENE,
    SNAPSHOT,
    GAME_ENDING,
    COMMAND,
    GAMES_RECOUNT,
    END_MATCH
} MSSG_HEADER;

// Codification of the edges of the  groundBlocks
typedef enum: uint8_t { NONE_TB = 1, TP, BTTM, BOTH_TB } VISIBILITY_BOTTOM_TOP;
typedef enum: uint8_t { NONE_RL = 1, RG, LF, BOTH_RL } VISIBILITY_RIGTH_LEFT;


#endif
