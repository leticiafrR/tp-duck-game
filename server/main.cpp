#include "server.h"

int main() {
    Server server;
    server.keepServing();
    server.closeServing();
    return 0;
}
