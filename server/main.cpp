#include "constants.h"
#include "server.h"

int main() {
    Server server;
    server.keepServing();
    server.closeServing();
    return SUCCESS_EXIT;
}
