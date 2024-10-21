#ifndef DATAMOVE_H
#define DATAMOVE_H

#include <string>

#include <stdint.h>

struct dataMove {
    bool block;              // cppcheck-suppress unusedStructMember
    std::string playerName;  // cppcheck-suppress unusedStructMember
    uint8_t ID;              // cppcheck-suppress unusedStructMember

    dataMove(): block(false), playerName(), ID(0) {}
};

#endif
