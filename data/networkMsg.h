#ifndef NETWORK_MSG_
#define NETWORK_MSG_

#include <vector>

#include "dataMatch.h"
#include "id.h"

struct NetworkMsg {
    virtual ~NetworkMsg() = default;
};
// wrappers for booleans that  cannot inherit from NetworkMssg
struct ResultJoining: public NetworkMsg {
    bool joined;
    explicit ResultJoining(bool _joined): joined(_joined) {}
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
