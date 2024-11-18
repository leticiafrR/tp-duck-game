#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>
#include <memory>
#include <string>

#include "common/queue.h"
#include "common/thread.h"
#include "data/networkMsg.h"

#include "ClientProtocol.h"
#include "Sender.h"

// void BindClient(std::atomic<MatchID_t>& matchSelection, ClientProtocol& protocol,
//                 Queue<std::shared_ptr<NetworkMsg>>& msgQueue) {
//     while (matchSelection == 0) {
//         msgQueue.push(protocol.receiveAvailableMatches());
//     }

//     std::shared_ptr<NetworkMsg> msg = protocol.receiveResultJoining();
//     msgQueue.push(msg);
//     if (!dynamic_pointer_cast<ResultJoining>(msg)->joined) {
//         BindClient(matchSelection, protocol, msgQueue);
//     }
// }
class Receiver: public Thread {
private:
    ClientProtocol& protocol;
    Queue<std::shared_ptr<NetworkMsg>>& msgQueue;
    Sender sender;
    std::string name;
    std::atomic<MatchID_t>& matchID;

public:
    Receiver(ClientProtocol& protocol, Queue<std::shared_ptr<NetworkMsg>>& msgQueue,
             Queue<CommandCode>& cmmdQueue, const std::string& name, std::atomic<MatchID_t>& id):
            protocol(protocol),
            msgQueue(msgQueue),
            sender(protocol, cmmdQueue),
            name(name),
            matchID(id) {}

    void run() override {
        try {
            protocol.sendNickname(name);
            // bind
            //  MatchBinder::BindClient(matchSelection,protocol,msgQueue);
            // BindClient(matchSelection, protocol, msgQueue);
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
