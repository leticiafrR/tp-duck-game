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

    PlayerID_t idClient;

    SenderThread sender;

    ServerProtocol protocol;

    void receiveLoop();

public:
    explicit ReceiverThread(Match& match, Socket&& sktPeer, PlayerID_t idClient);

    void run() override;

    /* Method that softly ends the receiver, definitely ends the sending thread (if it has not
     * finished because of the client disconnection) by killing it, once done this ends the
     * protocool communication with the client which would make the receiver end definitely */

    /*  The explicit call to ReceiverThread::join() has to be done. */
    void kill();

    ~ReceiverThread() override;
};
#endif
