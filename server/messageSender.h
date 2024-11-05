#ifndef MESSAGE_SENDER
#define MESSAGE_SENDER

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

/**************************** ABSTRACT class: THE  MESSAGES********************************/
class MessageSender {
public:
    virtual void execute(ServerProtocol& protocol) const = 0;
};

/******************************* MATCH START SETTING MSSG *********************************/

class MatchStartSender: public MessageSender {
private:
    const MatchStartDto matchStartDto;

public:
    MatchStartSender(std::vector<PlayerData> playersData, Vector2D duckSize);

    void execute(ServerProtocol& protocol) const override;
};

/******************************* GAME START SETTINGS MSSG *********************************/

class GameSceneSender: public MessageSender {
private:
    const GameSceneDto gameScene;

public:
    explicit GameSceneSender(GameSceneDto gameScene);
    void execute(ServerProtocol& protocol) const override;
};

/******************************* GAME UPDATE MSSG *********************************/
// must contain a boolean indicating if the game has been won
class GameUpdateSender: public MessageSender {
private:
    const Snapshot snapshot;

public:
    explicit GameUpdateSender(Snapshot snapshot);
    void execute(ServerProtocol& protocol) const override;
};

/********************************* GAMES RECOUNT MSSG ************************************/

class GamesRecountSender: public MessageSender {
private:
    const GamesRecountDto gamesRecount;

public:
    explicit GamesRecountSender(std::unordered_map<PlayerID_t, int> results, bool matchEnded);
    void execute(ServerProtocol& protocol) const override;
};

/************************************* MATCH RESULT MSSG ************************************/
class MatchExitSender: public MessageSender {
private:
    PlayerID_t finalWinner;

public:
    explicit MatchExitSender(PlayerID_t finalWinner);
    // this method sends the winner of all the match and also closes the munication with the client
    void execute(ServerProtocol& protocol) const override;
};

struct PlayerInfo {
    std::string nickName;
    Queue<std::shared_ptr<MessageSender>>* senderQueue;
    // cppcheck-suppress passedByValue
    PlayerInfo(std::string nickName, Queue<std::shared_ptr<MessageSender>>* senderQueue):
            nickName(nickName), senderQueue(senderQueue) {}
};


#endif
