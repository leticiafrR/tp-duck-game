#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <list>
#include <utility>

#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"

#include "match.h"
#include "receiver.h"

class AcceptorThread: public Thread {
private:
    Socket skt;
    std::list<ReceiverThread*> clients;
    Match match;

    void acceptLoop();
    void reapDead();
    // void killAll();
public:
    explicit AcceptorThread(const char* servname);
    void run() override;

    // not copyable
    AcceptorThread(const AcceptorThread&) = delete;
    AcceptorThread& operator=(const AcceptorThread&) = delete;

    // not movable
    AcceptorThread(AcceptorThread&&) = delete;
    AcceptorThread& operator=(AcceptorThread&&) = delete;
};

#endif
