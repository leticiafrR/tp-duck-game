#include <iostream>

#include "acceptor.h"

#define QUIT "q"

void startDummyMatch(const char* port);

int main(int argc, char* argv[]) {
    try {
        if (argc >= 2) {

            startDummyMatch(argv[1]);
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

void startDummyMatch(const char* port) {
    AcceptorThread* acceptor = new AcceptorThread(port);
    acceptor->start();
    holdClosure();
    // kill the match and the clients connected
    acceptor->forceClosure();
    acceptor->join();
    delete acceptor;
}
