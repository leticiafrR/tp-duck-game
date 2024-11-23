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
    Queue<std::shared_ptr<NetworkMsg>> msgQueue;
    Queue<Command> cmmdQueue;
    Queue<std::optional<MatchSelection>> matchSelections;
    Receiver* receiver;

public:
    Client(const char* servname, const char* hostname, const std::string& name):
            protocol(std::move(Socket(hostname, servname))),
            msgQueue(),
            cmmdQueue(),
            receiver(new Receiver(protocol, msgQueue, cmmdQueue, name, matchSelections)) {
        receiver->start();
    }

    void Refresh() {
        // Empty selection to denote refresh
        std::optional<MatchSelection> selection{};
        matchSelections.try_push(selection);
    }
    void SelectMatch(uint16_t matchID, uint8_t playersPerConnection) {
        std::optional<MatchSelection> selection = MatchSelection(matchID, playersPerConnection);
        matchSelections.try_push(selection);
    }

    void CreateMatch(uint8_t playersPerConnection) {
        std::optional<MatchSelection> createSelection = MatchSelection(0, playersPerConnection);
        matchSelections.try_push(createSelection);
    }

    void StartMatch() {
        std::optional<MatchSelection> itentionStart{};
        matchSelections.try_push(itentionStart);
    }


    bool TrySendRequest(const Command& cmmd) { return cmmdQueue.try_push(cmmd); }

    template <typename NetworkMsgDerivedClass>
    bool TryRecvNetworkMsg(std::shared_ptr<NetworkMsgDerivedClass>& concretMsg) {
        std::shared_ptr<NetworkMsg> msg;
        if (msgQueue.try_pop(msg)) {
            concretMsg = dynamic_pointer_cast<NetworkMsgDerivedClass>(msg);
            return true;
        }
        return false;
    }

    ~Client() {
        // receiver->kill();
        receiver->stop();
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
