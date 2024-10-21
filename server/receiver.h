#ifndef RECEIVER_H
#define RECEIVER_H

#include <utility>

#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"

#include "match.h"
#include "monitorMatches.h"
#include "sender.h"

class ProtocolServer;
class Lobby;

class ReceiverThread: public Thread {
private:
    MonitorMatches& matches;
    ProtocolServer protocol;
    size_t idClient;
    Match* myMatch;
    void receiveLoop();

public:
    explicit ReceiverThread(MonitorMatches& matches, Socket sktPeer, size_t idClient);
    void run() override;
    void forceEnd();
};
#endif
