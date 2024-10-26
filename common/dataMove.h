#ifndef DATAMOVE_H
#define DATAMOVE_H

#include <string>

#include <stdint.h>

struct dataMove {
    bool block;
    std::string playerName;
    uint8_t ID;

    dataMove(): block(false), playerName(), ID(0) {}
};

#endif
