#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>
#include <memory>

#include "common/queue.h"
#include "common/thread.h"
#include "data/networkMsg.h"

#include "ClientProtocol.h"
#include "Sender.h"

class Receiver: public Thread {
private:
    ClientProtocol& protocol;
    Queue<std::shared_ptr<NetworkMsg>>& msgQueue;  // mensajes polimorficos
    Sender sender;
    // std::string username;
public:
    Receiver(ClientProtocol& protocol, Queue<std::shared_ptr<NetworkMsg>>& msgQueue,
             Queue<CommandCode>& cmmdQueue):
            protocol(protocol), msgQueue(msgQueue), sender(protocol, cmmdQueue) {}

    void run() override {
        std::cout << "[RECEIVER]: el receiver esta corriendo\n";
        try {
            std::cout << "[RECEIVER]: se intenta enviar el nickname\n";
            protocol.sendNickname("Messi");
            std::cout << "[RECEIVER]: se logrò enviar el nickname\n";

            sender.start();
            while (_keep_running) {
                // trata de recibir un mensaje de network, y lo pushea a la queue
                std::shared_ptr<NetworkMsg> msg =
                        protocol.receiveMessage();  // si es que se bloquea aqui se soluciona
                                                    // shutdowning la queue
                msgQueue.push(msg);
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "ERROR RECEIVE:" << e.what() << std::endl;
        } catch (...) {
            std::cerr << "ERROR: An unkown error was catched at receiving a message from the server"
                      << std::endl;
        }
    }

    void kill() {
        sender.kill();
        if (sender.is_alive()) {
            sender.join();
        }
        protocol.endConnection();
    }

    void Saludar() { std::cout << "[CLIENTE RECEIVER]: Hola\n"; }
};


#endif
