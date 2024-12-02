#ifndef MESSAGE_SENDER
#define MESSAGE_SENDER

#include <exception>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include "common/Transform.h"
#include "common/queue.h"
#include "common/safeMap.h"

#include "serverProtocol.h"

/********************** ABSTRACT class: to send different messages****************************/
class MessageSender {
public:
    virtual void execute(ServerProtocol& protocol) const = 0;
    virtual ~MessageSender() = default;
};

/******************************* MATCH START SETTING SENDER *********************************/

class MatchStartSender: public MessageSender {
private:
    const MatchStartDto matchStartDto;

public:
    MatchStartSender(const std::vector<PlayerData>& playersData, Vector2D duckSize);
    void execute(ServerProtocol& protocol) const override;
};

/******************************* GAME START SETTINGS MSSG *********************************/

class GameSceneSender: public MessageSender {
private:
    const GameSceneDto gameScene;

public:
    explicit GameSceneSender(const GameSceneDto& gameScene);
    void execute(ServerProtocol& protocol) const override;
};

/******************************* GAME UPDATE MSSG *********************************/

class GameSnapshotSender: public MessageSender {
private:
    const Snapshot snapshot;

public:
    explicit GameSnapshotSender(const Snapshot& snapshot);
    void execute(ServerProtocol& protocol) const override;
};
/******************************* GAME ENDDING SENDER *********************************/

class GameEndingSender: public MessageSender {
private:
    const bool finalGroupGame;

public:
    explicit GameEndingSender(bool finalGroupGame);
    void execute(ServerProtocol& protocol) const override;
};

/********************************* GAMES RECOUNT SENDER ************************************/

class GamesRecountSender: public MessageSender {
private:
    const GamesRecountDto gamesRecount;

public:
    explicit GamesRecountSender(const std::unordered_map<PlayerID_t, int>& results,
                                bool matchEnded);
    void execute(ServerProtocol& protocol) const override;
};

/************************************* MATCH RESULT SENDER ************************************/
class MatchExitSender: public MessageSender {
private:
    PlayerID_t finalWinner;

public:
    explicit MatchExitSender(PlayerID_t finalWinner);
    void execute(ServerProtocol& protocol) const override;
};


#endif
