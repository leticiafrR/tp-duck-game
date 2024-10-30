#ifndef SENDER_H
#define SENDER_H
#include <cstddef>

#include "../common/queue.h"
#include "../common/thread.h"

#include "match.h"
#include "serverProtocol.h"

#define MAX_MESSAGES 250
class SenderThread: public Thread {
private:
    Queue<SnapShoot> senderQueue;
    ServerProtocol& protocol;
    // its up to the sender to, when finished the sendingLoop, ask the match to logOut this client.
    Match& match;
    PlayerID_t idClient;

    void sendLoop();

public:
    explicit SenderThread(ServerProtocol& protocol, Match& match, PlayerID_t idClient);

    Queue<SnapShoot>* getSenderQueue();

    void run() override;

    /* The method causes the sending thread to stop accepting new snapshoots in its queue (closing
     * it) so that it can finish sending the snapshoots it has at the moment and then finish its
     * execution in an orderly manner.*/
    void kill();

    ~SenderThread() override;
};

#endif
