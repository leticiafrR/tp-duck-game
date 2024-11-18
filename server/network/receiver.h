#ifndef RECEIVER_H
#define RECEIVER_H

#include <memory>
#include <utility>

#include "common/queue.h"
#include "common/thread.h"
#include "data/id.h"

#include "serverProtocol.h"


struct Command;  // must include this in receiver.cpp

class ReceiverThread: public Thread {
private:
    std::shared_ptr<Queue<Command>> matchQueue;

    PlayerID_t idClient;

    ServerProtocol& protocol;

public:
    explicit ReceiverThread(PlayerID_t idClient, std::shared_ptr<Queue<Command>> matchQueue,
                            ServerProtocol& protocol);

    void run() override;

    /* Method that softly ends the receiver, definitely ends the sending thread (if it has not
     * finished because of the client disconnection) by killing it, once done this ends the
     * protocool communication with the client which would make the receiver end definitely */

    /*  The explicit call to ReceiverThread::join() has to be done. */
    void kill();

    //~ReceiverThread() override;
};
#endif
