#ifndef NETWORK_MSG_
#define NETWORK_MSG_

struct NetworkMsg {};
// wrappers for booleans that  cannot inherit from NetworkMssg
struct ResultJoining: public NetworkMsg {
    bool joined;
    explicit ResultJoining(bool _joined): joined(_joined) {}
};

struct FinalGameGroup: public NetworkMsg {
    bool finalGroupGame;
    explicit FinalGameGroup(bool _finalGroupGame): finalGroupGame(_finalGroupGame) {}
};

#endif
