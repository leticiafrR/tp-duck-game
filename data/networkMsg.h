#ifndef NETWORK_MSG_
#define NETWORK_MSG_

#include <vector>

#include "data/errorCodesJoinMatch.h"

#include "dataMatch.h"
#include "id.h"

struct NetworkMsg {
    virtual ~NetworkMsg() = default;
};

// wrappers for booleans that  cannot inherit from NetworkMssg
struct ResultJoining: public NetworkMsg {
    uint8_t eCode;
    explicit ResultJoining(uint8_t _eCode): eCode(_eCode) {}
};

struct ResultStartingMatch: public NetworkMsg {
    bool success;
    explicit ResultStartingMatch(bool _success): success(_success) {}
};

struct FinalGroupGame: public NetworkMsg {
    bool finalGroupGame;
    explicit FinalGroupGame(bool _finalGroupGame): finalGroupGame(_finalGroupGame) {}
};

struct FinalWinner: public NetworkMsg {
    PlayerID_t winner;
    explicit FinalWinner(PlayerID_t _winner): winner(_winner) {}
};

struct AvailableMatches: public NetworkMsg {
    std::vector<DataMatch> matches;
    explicit AvailableMatches(const std::vector<DataMatch>& _matches): matches(_matches) {}
};

#endif
