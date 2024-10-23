#ifndef DATAMOVE_H
#define DATAMOVE_H

#include <string>

#include <stdint.h>

struct dataMove {
    [[clang::supress_unused]] bool block;
    [[clang::supress_unused]] std::string playerName;
    [[clang::supress_unused]] uint8_t ID;

    dataMove(): block(false), playerName(), ID(0) {}
};

#endif
