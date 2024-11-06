#include <iostream>

#include "acceptor.h"
#include "config.h"

#define QUIT "q"

void startDummyMatch(const char* port, Config& config);

int main(int argc, char* argv[]) {
    try {
        if (argc >= 2) {
            Config config;
            startDummyMatch(argv[1], std::ref(config));
            return 0;

        } else {
            std::cerr << "Bad program call. Expected " << argv[0] << " <servername>" << std::endl;
            return 1;
        }
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
