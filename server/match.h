#ifndef MATCH_H
#define MATCH_H

#include <atomic>
#include <memory>
#include <mutex>
#include <vector>

#include "common/queue.h"
#include "common/safeMap.h"
#include "common/thread.h"
#include "data/dataTransferObjects.h"
#include "data/id.h"

#include "clientInfo.h"
#include "config.h"
#include "matchStatus.h"


struct Command;
struct DataMatch;
class MessageSender;

class Match: public Thread {
private:
    std::atomic<MATCH_STATUS> matchStatus;
    std::atomic<bool> _hadStarted = false;
    std::atomic<uint8_t> currentPlayers = 0;

    uint16_t matchHost;

    std::shared_ptr<Queue<Command>> matchQueue;

    SafeMap<uint16_t, Queue<std::shared_ptr<MessageSender>>*> clientsQueues;
    // clave el connection id
    SafeMap<uint16_t, ClientInfo>
            playersPerClient;  // con la info de nickname base, connectionID, numberOfPlayers

    const Config& config;

    std::mutex endMatch;

public:
    explicit Match(const Config& config, uint16_t matchHost);

    void loadDataIfAvailble(std::vector<DataMatch>& availableMatches);

    std::shared_ptr<Queue<Command>> logInClient(const ClientInfo& connectionInfo,
                                                Queue<std::shared_ptr<MessageSender>>* clientQueue,
                                                uint8_t& eCode);

    bool readyToStart();

    bool isOver();

    bool hadStarted();

    void logOutClient(uint16_t connectionID);

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
