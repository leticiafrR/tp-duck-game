#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>
#include <memory>
#include <string>

#include "common/matchBinder.h"
#include "common/queue.h"
#include "common/thread.h"
#include "data/networkMsg.h"

#include "ClientProtocol.h"
#include "Sender.h"
#include "bindCmmd.h"

class Receiver: public Thread {
private:
    ClientProtocol& protocol;
    Queue<std::shared_ptr<NetworkMsg>>& msgQueue;
    Sender sender;
    std::string name;
    Queue<BindCmmd>& bindingCommands;

public:
    Receiver(ClientProtocol& protocol, Queue<std::shared_ptr<NetworkMsg>>& msgQueue,
             Queue<CommandCode>& cmmdQueue, const std::string& name,
             Queue<BindCmmd>& bindingCommands):
            protocol(protocol),
            msgQueue(msgQueue),
            sender(protocol, cmmdQueue),
            name(name),
            bindingCommands(bindingCommands) {}

    void run() override {
        try {
            protocol.sendNickname(name);
            PlayerID_t playerID = protocol.receiveMyID();
            std::cout << "[Receiver]: your id is: " << playerID << std::endl;
            MatchBinder::ClientBind(playerID, msgQueue, bindingCommands, protocol);
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
