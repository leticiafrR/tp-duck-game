#ifndef DATAMATCH_H
#define DATAMATCH_H

#include <string>

struct dataMatch {
    [[clang::supress_unused]] std::string clientName;
    [[clang::supress_unused]] size_t ID;
    [[clang::supress_unused]] uint8_t quantityPlayers;
    [[clang::supress_unused]] uint8_t MAXPlayers;
    dataMatch(): clientName(), ID(0), quantityPlayers(), MAXPlayers() {}
};
#endif
