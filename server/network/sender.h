#ifndef SENDER_H
#define SENDER_H

#include <cstddef>
#include <memory>
#include <string>
#include <utility>

#include "../matchesMonitor.h"
#include "common/queue.h"
#include "data/id.h"

#include "serverProtocol.h"

#define MAX_MESSAGES 250

class MessageSender;

class SenderThread: public Thread {
private:
    MatchesMonitor& matches;

    Queue<std::shared_ptr<MessageSender>> senderQueue;

    ServerProtocol protocol;

    PlayerID_t playerID;

    std::atomic<bool> _joinedAMatch = false;

    void sendLoop(PlayerID_t matchID);

public:
    explicit SenderThread(Socket&& sktPeer, MatchesMonitor& matches, PlayerID_t playerID);

    void run() override;

    void kill();

    ~SenderThread() override;
};

#endif
