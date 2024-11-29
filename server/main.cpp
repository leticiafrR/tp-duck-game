#include <exception>

#include "constants.h"
#include "server.h"

#define DEFAULT_PORT "8080"

int main(int argc, const char** argv) {
    auto port = DEFAULT_PORT;
    if (argc == 2) {
        port = argv[1];
    }
    try {
        Server server;
        server.startServing(port);
        server.closeServing();
        return SUCCESS_EXIT;
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
    }
    return FAILURE_EXIT;
}
