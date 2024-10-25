#ifndef PARSER_H
#define PARSER_H

#include <cstdint>
#include <string>

typedef enum: uint8_t {
    UP_ID = 1,
    RIGHT_ID,
    LEFT_ID,
    DOWN_ID,
    SHOOT_ID,
    KEY_UP_ID,
    KEY_DOWN_ID,
} KEYS;

typedef enum: uint8_t {
    CITY_ID = 1,
    FOREST_ID,
} BACKGROUNDS;


class Parser {

public:
    std::string WhatCommandIs(const uint8_t& ID);
    void WhatWeaponIs(const uint8_t& ID);
    void WhatSkinIs(const uint8_t& ID);
    std::string WhatBackGroundIs(const uint8_t& ID);
};
#endif
