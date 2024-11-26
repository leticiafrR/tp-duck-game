#include "server.h"

#include <string>

#define QUIT "q"

Server::Server(const char* port):
        config(), matches(config), acceptor(std::make_unique<AcceptorThread>(port, config)) {
    acceptor->start();
}

void Server::keepServing() {
    std::string in;
    do {
        std::cin >> in;
    } while (in != QUIT);
}

void Server::closeServing() {
    acceptor->forceClosure();
    acceptor->join();
}
