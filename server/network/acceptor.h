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

    void killClients();

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
