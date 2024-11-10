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
    Queue<std::shared_ptr<NetworkMsg>>& msgQueue;
    Sender sender;

public:
    Receiver(ClientProtocol& protocol, Queue<std::shared_ptr<NetworkMsg>>& msgQueue,
             Queue<CommandCode>& cmmdQueue):
            protocol(protocol), msgQueue(msgQueue), sender(protocol, cmmdQueue) {}

    void run() override {
        try {
            protocol.sendNickname("Messi");
            sender.start();
            while (_keep_running) {
                std::shared_ptr<NetworkMsg> msg = protocol.receiveMessage();
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
};


#endif
