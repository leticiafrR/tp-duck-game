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
#include "../common/Vector2D.h"
#include "../common/dataTransferObjects.h"
#include "../common/queue.h"
#include "../common/safeMap.h"
#include "../common/snapShoot.h"
#include "../data/id.h"

#include "serverProtocol.h"

// a la par definirè los data objects que recibirà el cliente (structs que empaqueten esta
// informaciòn)
struct PlayerInfo {
    std::string nickName;
    Queue<std::shared_ptr<ClientMessage>>* senderQueue;  // cppcheck-suppress unusedStructMember
};


/**************************** ABSTRACT class: THE  MESSAGES********************************/
class ClientMessage {
public:
    virtual bool sendMyself(ServerProtocol& protocol) const = 0;
};

/******************************* MATCH START SETTING MSSG *********************************/

class MatchStartSettings: public ClientMessage {
private:
    // yo lo construyo
    std::unordered_map<int, std::tuple<PlayerID_t, std::string>> skinsAssignation;
    // referencia a lo que me devuelve config (jamas cambiarà)
    const Vector2D duckSize;

public:
    // throw a runtime exception if assigning unique skins to each player in the game cannot be done
    // because there are not enough skins
    MatchStartSettings(SafeMap<PlayerID_t, PlayerInfo>& players, int numberSkins,
                       Vector2D duckSize);

    bool sendMyself(ServerProtocol& protocol) const override;
};

/******************************* GAME START SETTINGS MSSG *********************************/

class GameStartSettings: public ClientMessage {

private:
    const std::string theme;
    const std::vector<Transform> platforms;

public:
    GameStartSettings(std::string theme, std::vector<Transform> platforms);

    bool sendMyself(ServerProtocol& protocol) const override;
};

/******************************* GAME UPDATE MSSG *********************************/
// must contain a boolean indicating if the game has been won
class GameUpdate: public ClientMessage {
private:
    const SnapShoot snapShoot;

public:
    explicit GameUpdate(SnapShoot);
    bool sendMyself(ServerProtocol& protocol) const override;
};

// /********************************* GAMES RECOUNT MSSG ************************************/

class GamesRecount: public ClientMessage {
private:
    const std::unordered_map<PlayerID_t, int> results;
    bool matchEnded;

public:
    explicit GamesRecount(std::unordered_map<PlayerID_t, int> results, bool matchEnded);

    bool sendMyself(ServerProtocol& protocol) const override;
};

/************************************* MATCH RESULT MSSG ************************************/
class MatchResult: public ClientMessage {
private:
    PlayerID_t finalWinner;

public:
    explicit MatchResult(PlayerID_t finalWinner);
    bool sendMyself(ServerProtocol& protocol) const override;
};

#endif
