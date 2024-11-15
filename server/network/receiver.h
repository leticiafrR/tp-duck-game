#ifndef RECEIVER_H
#define RECEIVER_H

#include <memory>
#include <utility>
// ya se no se utiliza a la match directamente
#include "../matchesMonitor.h"

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
