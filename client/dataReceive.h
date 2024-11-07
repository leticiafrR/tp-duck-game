#ifndef DATARECEIVE_H
#define DATARECEIVE_H

#include <string>

#include "data/dataTransferObjects.h"

typedef enum: uint8_t {
    DEFAULT,
    MATCH_START,
    GAME_START,
    SNAPSHOT_DATA,
    GAME_RECOUNT,
    WINNER,
} DataType;

struct DataRecieve {
    virtual uint8_t WhatTypeIs() { return DEFAULT; }
    virtual ~DataRecieve() = default;
};

struct DataMatchStart: public DataRecieve {
    MatchStartDto settings;
    uint8_t WhatTypeIs() override { return MATCH_START; }
    explicit DataMatchStart(const MatchStartDto& sett): settings(sett) {}
};
struct DataScene: public DataRecieve {
    GameSceneDto scene;
    uint8_t WhatTypeIs() override { return GAME_START; }
    explicit DataScene(GameSceneDto& s): scene(s) {}
};
/*
struct DataSnapshot: public DataRecieve {
    Snapshot snapshot;
    uint8_t WhatTypeIs() override { return SNAPSHOT; }
    explicit DataSnapshot(const Snapshot& snap): snapshot(snap) {}
};*/
struct DataGameRecount: public DataRecieve {
    GamesRecountDto recount;
    uint8_t WhatTypeIs() override { return GAME_RECOUNT; }
    explicit DataGameRecount(const GamesRecountDto& gamecount): recount(gamecount) {}
};
struct DataWinner: public DataRecieve {
    PlayerID_t ID;
    uint8_t WhatTypeIs() override { return WINNER; }
    explicit DataWinner(const PlayerID_t& ID): ID(ID) {}
};
#endif
