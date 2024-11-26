#ifndef RECEIVER_H
#define RECEIVER_H

#include <memory>
#include <utility>

#include "../matchesMonitor.h"
#include "common/queue.h"
#include "common/thread.h"
#include "data/id.h"

#include "serverProtocol.h"


struct Command;

class ReceiverThread: public Thread {
private:
    MatchesMonitor& matches;
    std::shared_ptr<Queue<Command>> matchQueue;
    uint16_t matchID;

    uint16_t connectionId;
    uint8_t playersPerConnection;
    ServerProtocol& protocol;


public:
    explicit ReceiverThread(MatchesMonitor& matches, std::shared_ptr<Queue<Command>> matchQueue,
                            uint16_t matchID, uint16_t clientID, uint8_t playersPerConnection,
                            ServerProtocol& protocol);

    void run() override;
};
#endif
