#ifndef COMMUNICATION_CODES_H
#define COMMUNICATION_CODES_H

#include <cstdint>

typedef enum: uint8_t {
    NICKNAME = 1,
    RESULT_JOINING,
    MATCH_STARTING,
    GAME_SCENE,
    SNAPSHOT,
    COMMAND,
    GAMES_RECOUNT,
    END_MATCH
} MSSG_HEADER;

// Codification of the edges of the  groundBlocks
typedef enum: uint8_t { NONE_TB = 1, TP, BTTM, BOTH_TB } V_BTTM_TOP;
typedef enum: uint8_t { NONE_RL = 1, RG, LF, BOTH_RL } V_RG_LF;


#endif
