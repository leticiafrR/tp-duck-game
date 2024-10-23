#ifndef DATAMATCH_H
#define DATAMATCH_H

#include <string>

struct dataMatch {
    std::string clientName;   // cppcheck-suppress unusedStructMember
    size_t ID;                // cppcheck-suppress unusedStructMember
    uint8_t quantityPlayers;  // cppcheck-suppress unusedStructMember
    uint8_t MAXPlayers;       // cppcheck-suppress unusedStructMember
    dataMatch(): clientName(), ID(0), quantityPlayers(), MAXPlayers() {}
};
#endif
