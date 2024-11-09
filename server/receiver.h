#ifndef RECEIVER_H
#define RECEIVER_H

#include <utility>

#include "match.h"

class ReceiverThread: public Thread {
private:
    Match& match;

    PlayerID_t idClient;

    ServerProtocol& protocol;

    void receiveLoop();

public:
    explicit ReceiverThread(PlayerID_t idClient, Match& match, ServerProtocol& protocol);

    void run() override;

    /* Method that softly ends the receiver, definitely ends the sending thread (if it has not
     * finished because of the client disconnection) by killing it, once done this ends the
     * protocool communication with the client which would make the receiver end definitely */

    /*  The explicit call to ReceiverThread::join() has to be done. */
    void kill();

    //~ReceiverThread() override;
};
#endif
