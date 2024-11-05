#ifndef SENDER_H
#define SENDER_H
#include <cstddef>
#include <memory>
#include <string>
#include <utility>

#include "../common/queue.h"
#include "../common/thread.h"

#include "match.h"
#include "receiver.h"
#include "serverProtocol.h"

#define MAX_MESSAGES 250

class SenderThread: public Thread {
private:
    Match& match;
    Queue<std::shared_ptr<MessageSender>> senderQueue;
    ServerProtocol protocol;
    PlayerID_t idClient;
    std::atomic<bool> _joinedAMatch = false;

    void sendLoop();

public:
    explicit SenderThread(Socket&& sktPeer, Match& match, PlayerID_t idClient);
    bool joinedAMatch();

    void run() override;

    void kill();

    /* method that kills the client only if hasnt joined a match, if it has, that match is the one
     * who kills the threads of this client (as it is one of its participants). To make sure to kill
     * match force the end of the match.*/
    ~SenderThread() override;
};

#endif
