#ifndef RECEIVER_H
#define RECEIVER_H

#include <utility>

#include "../common/liberror.h"
#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"

#include "match.h"
#include "sender.h"
#include "serverProtocol.h"

class ReceiverThread: public Thread {
private:
    // we push to the queue of the match through a method bc there are some verifications in the
    // state of the match that could dont let us to push
    Match& match;

    size_t idClient;

    SenderThread sender;

    ServerProtocol protocol;


    void receiveLoop();

public:
    // initializates the command queue where the reciever pushes with the command queue that the
    // match recieved gives us and also binds this client with the only one match that we have (i
    // mean its queue of messages is included to the broadcast list)
    explicit ReceiverThread(Match& match, Socket&& sktPeer, size_t idClient);

    void run() override;
    void kill();

    ~ReceiverThread() override;
};
#endif
