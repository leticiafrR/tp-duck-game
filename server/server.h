#ifndef SERVER_H
#define SERVER_H

#include <memory>

#include "network/acceptor.h"

#include "config.h"
#include "matchesMonitor.h"

class Server {
private:
    Config config;
    MatchesMonitor matches;
    std::unique_ptr<AcceptorThread> acceptor;

public:
    Server();
    void startServing(const char* port);
    void closeServing();

    // not copyable
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
    // not movable
    Server(Server&&) = delete;
    Server& operator=(Server&&) = delete;
};

#endif
