#include "network/Client.h"

int main() {
    Client c("8080", "127.0.0.1");
    c.Saludar();
    return 0;
}
