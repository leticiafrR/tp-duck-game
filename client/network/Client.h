#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "common/queue.h"
#include "common/thread.h"
#include "data/command.h"
#include "data/networkMsg.h"

#include "Receiver.h"


class Client {
private:
    ClientProtocol protocol;
    Queue<std::shared_ptr<NetworkMsg>> msgQueue;  // mensajes polimorficos
    Queue<CommandCode> cmmdQueue;                 // comandos unicos
    Receiver* receiver;                           // lanza al sender
public:
    Client(const char* servname, const char* hostname):
            protocol(std::move(Socket(hostname, servname))),
            msgQueue(),
            cmmdQueue(),
            receiver(new Receiver(protocol, msgQueue, cmmdQueue)) {
        receiver->start();
    }

    bool TrySendRequest(const CommandCode& cmmd) { return cmmdQueue.try_push(cmmd); }

    // retorna true si el puntero si fue actualizado
    bool TryRecvNetworkMsg(std::shared_ptr<NetworkMsg>& msg) { return msgQueue.try_pop(msg); }

    void Saludar() { std::cout << "HOLA\n"; }

    ~Client() {
        receiver->kill();
        if (receiver->is_alive()) {
            receiver->join();
        }
        delete receiver;
    }
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    Client(Client&& other) = delete;
    Client& operator=(Client&& other) = delete;
};

#endif
