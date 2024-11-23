#ifndef DATA_MATCH_
#define DATA_MATCH_

#include <cstdint>
#include <string>

#include "id.h"
#define REFRESHED_ID_CODE 0

struct DataMatch {
    uint8_t currentPlayers;
    uint8_t maxPlayers;
    uint16_t matchID;
    std::string creatorNickname;

    DataMatch(uint8_t _currentPlayers, uint8_t _maxPlayers, uint16_t _matchID,
              const std::string& _creatorNickname):
            currentPlayers(_currentPlayers),
            maxPlayers(_maxPlayers),
            matchID(_matchID),
            creatorNickname(_creatorNickname) {}
};

#endif
