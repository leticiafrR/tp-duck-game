#include "parser.h"

#include "constant.h"

std::string Parser::WhatCommandIs(const uint8_t& ID) {
    switch (ID) {
        case UP_ID:
            return UP;
        case DOWN_ID:
            return DOWN;
        case LEFT_ID:
            return LEFT;
        case RIGHT_ID:
            return RIGHT;
        case SHOOT_ID:
            return SHOOT;
        case KEY_UP_ID:

        case KEY_DOWN_ID:

        default:
            break;
    }
    return "";
}

std::string Parser::WhatBackGroundIs(const uint8_t& ID) {
    switch (ID) {
        case CITY_ID:
            return CITY_BACKGROUND;
        case FOREST_ID:
            return FOREST_BACKGROUND;
        default:
            break;
    }
    return "";
}
