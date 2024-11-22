#ifndef MATCH_H
#define MATCH_H

#include <atomic>
#include <memory>
#include <mutex>
#include <vector>

#include "common/safeMap.h"
#include "common/thread.h"
#include "data/dataTransferObjects.h"
#include "data/id.h"

#include "config.h"
#include "matchStatus.h"
#include "playerInfo.h"


struct Command;
struct DataMatch;

class Match: public Thread {
private:
    std::atomic<MATCH_STATUS> matchStatus;
    std::atomic<bool> _hadStarted = false;

    PlayerID_t playerCreator;

    std::shared_ptr<Queue<Command>> commandQueue;

    SafeMap<PlayerID_t, PlayerInfo> players;

    const Config& config;

    std::mutex endMatch;

public:
    explicit Match(const Config& config, PlayerID_t playerCreator);

    void loadDataIfAvailble(std::vector<DataMatch>& availableMatches);

    std::shared_ptr<Queue<Command>> logInPlayer(PlayerID_t playerID, const PlayerInfo& playerInfo);

    bool hasEnoughPlayers();

    bool isOver();

    bool hadStarted();

    void logOutPlayer(PlayerID_t idClient);

    void run() override;

    void forceEnd();

    ~Match() = default;

private:
    bool isAvailable();

    std::vector<PlayerData> assignSkins(int numberSkins);

    void setEndOfMatch(PlayerID_t winner);

    void checkNumberPlayers();

    void broadcastMatchMssg(const std::shared_ptr<MessageSender>& message);
};

#endif
