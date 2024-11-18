#ifndef DATA_MATCH_
#define DATA_MATCH_

#include <string>

#include "id.h"

struct DataMatch {
    int currentPlayers;
    int maxPlayers;
    PlayerID_t matchID;
    std::string creatorNickname;

    DataMatch(int _currentPlayers, int _maxPlayers, PlayerID_t _matchID,
              const std::string& _creatorNickname):
            currentPlayers(_currentPlayers),
            maxPlayers(_maxPlayers),
            matchID(_matchID),
            creatorNickname(_creatorNickname) {}
};

#endif
