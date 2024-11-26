#include "constants.h"
#include "server.h"

#define DEFAULT_PORT "8080"

int main(int argc, const char** argv) {
    auto port = DEFAULT_PORT;
    if (argc == 2) {
        port = argv[1];
    }
    Server server(port);
    server.keepServing();
    server.closeServing();
    return SUCCESS_EXIT;
}
