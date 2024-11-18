
#include <iostream>
#include <string>
#include <utility>

#include "acceptor.h"
#include "config.h"

#define QUIT "q"


void startDummyMatch(const char* port, Config& config);

int main() {
    try {
        Config config;
        auto port = "8080";
        startDummyMatch(port, std::ref(config));
        return 0;
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what()
                  << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught." << std::endl;
        return 1;
    }
}

void holdClosure() {
    std::string in;
    do {
        std::cin >> in;
    } while (in != QUIT);
}

void startDummyMatch(const char* port, Config& config) {
    AcceptorThread* acceptor = new AcceptorThread(port, std::ref(config));
    acceptor->start();
    holdClosure();
    // kill the match and the clients connected
    acceptor->forceClosure();
    acceptor->join();
    delete acceptor;
}
