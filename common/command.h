#ifndef COMMAND_H
#define COMMAND_H

#include <string>

#include <stdint.h>

struct Command {
    [[clang::supress_unused]] bool block;
    [[clang::supress_unused]] std::string playerName;
    [[clang::supress_unused]] uint8_t commandID;
    [[clang::supress_unused]] uint8_t playerID;

    Command(): block(false), playerName(), commandID(0), playerID(0) {}
};

#endif
