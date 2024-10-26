#ifndef DATAMATCH_H
#define DATAMATCH_H

#include <string>

struct dataMatch {
    std::string clientName;
    size_t ID;
    uint8_t quantityPlayers;
    uint8_t MAXPlayers;
    dataMatch(): clientName(), ID(0), quantityPlayers(), MAXPlayers() {}
};
#endif
