#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>
#include <memory>
#include <optional>
#include <string>

#include "common/matchBinder.h"
#include "common/queue.h"
#include "common/thread.h"
#include "data/matchSelection.h"
#include "data/networkMsg.h"

#include "ClientProtocol.h"
#include "Sender.h"

class Receiver: public Thread {
private:
    ClientProtocol& protocol;
    Queue<std::shared_ptr<NetworkMsg>>& msgQueue;
    Sender sender;
    std::string name;
    Queue<std::optional<MatchSelection>>& matchSelections;
    std::atomic<uint16_t>& localID;

public:
    Receiver(ClientProtocol& protocol, Queue<std::shared_ptr<NetworkMsg>>& msgQueue,
             Queue<Command>& cmmdQueue, const std::string& name,
             Queue<std::optional<MatchSelection>>& matchSelections, std::atomic<uint16_t>& localID):
            protocol(protocol),
            msgQueue(msgQueue),
            sender(protocol, cmmdQueue),
            name(name),
            matchSelections(matchSelections),
            localID(localID) {}

    void run() override {
        try {
            protocol.sendNickname(name);
            localID = protocol.receiveLocalID();
            std::cout << "[Receiver]: Got the local id: " << localID << std::endl;

            MatchBinder::ClientBind(localID, msgQueue, matchSelections, protocol);

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

        msgQueue.close();
    }


    // supongo que deberìa estar para cuando el cliente cierra la app antes de que termine la
    // partida NOTA: jamas se usa, entoces jamas se joinea. el  sender ¿QUièn y donde se hace  el
    // join eplicito alreceiver=?
    void kill() {
        sender.kill();
        if (sender.is_alive()) {
            sender.join();
        }
        protocol.endConnection();
    }
};


#endif
