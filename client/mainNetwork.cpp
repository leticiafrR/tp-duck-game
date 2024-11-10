#include "network/Client.h"

int main() {
    Client c("8080", "127.0.0.1");
    char input;

    while (true) {
        std::cin >> input;
        if (input == 'q') {
            std::cout << "Exiting\n";
            break;
        }
        std::cout << "OUT\n";
    }
    // ClientProtocol protocol(std::move(Socket("127.0.0.1","8080")));
    // protocol.sendNickname("leti");
    return 0;
}
