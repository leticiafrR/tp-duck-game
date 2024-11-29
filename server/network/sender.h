#ifndef SENDER_H
#define SENDER_H

#include <cstddef>
#include <memory>
#include <string>
#include <utility>

#include "../matchesMonitor.h"
#include "common/queue.h"
#include "data/id.h"
#include "data/matchSelection.h"

#include "serverProtocol.h"

class MessageSender;

class SenderThread: public Thread {
private:
    MatchesMonitor& matches;
    MatchSelection finalSelection;
    Queue<std::shared_ptr<MessageSender>> senderQueue;
    ServerProtocol protocol;
    uint16_t connectionId;
    std::atomic<bool> _joinedAMatch = false;

public:
    explicit SenderThread(Socket&& sktPeer, MatchesMonitor& matches, uint16_t connectionId);
    void run() override;
    void kill();

private:
    void sendLoop();
    std::shared_ptr<Queue<Command>> bind();
    bool setClientProfile(ClientInfo& clientInfo);
    void hostClientStartMatch(uint16_t matchID);
    void handleBindingInterruption();
};

#endif
