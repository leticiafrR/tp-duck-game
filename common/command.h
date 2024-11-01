#ifndef COMMAND_H
#define COMMAND_H

#include <string>

#include <stdint.h>

struct Command {
    [[clang::supress_unused]] bool block;
    [[clang::supress_unused]] uint8_t commandID;
    [[clang::supress_unused]] uint32_t playerID;

    Command(): block(false), commandID(0), playerID(0) {}
};

#endif
