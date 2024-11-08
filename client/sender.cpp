#include "sender.h"

Sender::Sender(ClientProtocol& prot, Queue<CommandCode>& comm, const std::string& nickname):
        protocol(prot), commands(comm), /*nickname(nickname)*/ {
    protocol.sendNickname(nickname);
}

void Sender::run() {


    while (_keep_running) {
        Command msg = commands.pop();

        protocol.sendCommand(msg);
    }
}
