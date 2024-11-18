#include "server.h"

#include <string>

#define PORT "8080"
#define QUIT "q"

Server::Server(): config(), matches(config), acceptor(PORT, config) { acceptor.start(); }

void Server::keepServing() {
    std::string in;
    do {
        std::cin >> in;
    } while (in != QUIT);
}

void Server::closeServing() {
    acceptor.forceClosure();
    acceptor.join();
}
