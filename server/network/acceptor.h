#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <list>
#include <memory>
#include <utility>

#include "sender.h"

class AcceptorThread: public Thread {
private:
    Socket skt;
    std::list<std::unique_ptr<SenderThread>> clients;
    MatchesMonitor matchesMonitor;

    void acceptLoop();

    void reapDeadClients();

    /* This method first kills the clients (that havent joined a match), then it forces the end of
     * the matches and this will make sure to kill the communication threads of their participants.
     * Once donde this the only thing left if joining the threads of all the clients
     * and also the match*/
    void killAllClients();

public:
    explicit AcceptorThread(const char* servname, Config& config);

    void run() override;

    void forceClosure();

    // not copyable
    AcceptorThread(const AcceptorThread&) = delete;
    AcceptorThread& operator=(const AcceptorThread&) = delete;

    // not movable
    AcceptorThread(AcceptorThread&&) = delete;
    AcceptorThread& operator=(AcceptorThread&&) = delete;
};

#endif
