#ifndef CLIENT_MESSAGES_
#define CLIENT_MESSAGES_

#include <exception>
#include <memory>
#include <random>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../common/Transform.h"
#include "../common/queue.h"
#include "../common/safeMap.h"
#include "../common/snapShoot.h"
#include "../data/id.h"

#include "serverProtocol.h"

struct PlayerInfo {
    std::string nickName;
    Queue<std::shared_ptr<ClientMessage>>* senderQueue;  // cppcheck-suppress unusedStructMember
};


/**************************** ABSTRACT class: THE  MESSAGES********************************/
class ClientMessage {
public:
    virtual bool sendMyself(ServerProtocol& protocol) = 0;
};

/******************************* MATCH START SETTING MSSG *********************************/

class MatchStartSettings: public ClientMessage {
    std::unordered_map<int, std::tuple<PlayerID_t, std::string>> skinsAssignation;

public:
    // throw a runtime exception if assigning unique skins to each player in the game cannot be done
    // because there are not enough skins
    MatchStartSettings(SafeMap<PlayerID_t, PlayerInfo>& players, int numberSkins);
    bool sendMyself(ServerProtocol& protocol) override;
};

/******************************* GAME START SETTINGS MSSG *********************************/

class GameStartSettings: public ClientMessage {
    std::string theme;
    std::vector<Transform> gamePlatforms;

public:
    GameStartSettings(const std::string& theme, std::vector<Transform>&& gamePlatforms);
    bool sendMyself(ServerProtocol& protocol) override;
};

/******************************* GAME UPDATE MSSG *********************************/
// must contain a boolean indicating if the game has been won
class GameUpdate: public ClientMessage {
    SnapShoot snapShoot;

public:
    explicit GameUpdate(SnapShoot);
    bool sendMyself(ServerProtocol& protocol) override;
};

// /********************************* GAMES RECOUNT MSSG ************************************/

class GamesRecount: public ClientMessage {
    std::unordered_map<PlayerID_t, int> results;
    explicit GamesRecount(std::unordered_map<PlayerID_t, int> results);
    bool sendMyself(ServerProtocol& protocol) override;
};

/************************************* MATCH RESULT MSSG ************************************/
class MatchResult: public ClientMessage {
    PlayerID_t finalWinner;

public:
    explicit MatchResult(PlayerID_t finalWinner);
    bool sendMyself(ServerProtocol& protocol) override;
};

#endif
