#include "server.h"

#include <string>

#define QUIT "q"

Server::Server(): config(), matches(config) {}

void Server::startServing(const char* port) {
    acceptor = std::make_unique<AcceptorThread>(port, config);
    acceptor->start();
    std::string in;
    do {
        std::cin >> in;
    } while (in != QUIT);
}

void Server::closeServing() {
    acceptor->forceClosure();
    acceptor->join();
}
