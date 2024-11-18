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
    Queue<CommandCode> cmmdQueue;
    Queue<BindCmmd> bindingCommands;
    Receiver* receiver;

public:
    Client(const char* servname, const char* hostname, const std::string& name):
            protocol(std::move(Socket(hostname, servname))),
            msgQueue(),
            cmmdQueue(),
            receiver(new Receiver(protocol, msgQueue, cmmdQueue, name, bindingCommands)) {
        receiver->start();
    }

    void Refresh() { bindingCommands.try_push(BindCmmd(BindCmmdCode::REFRESH_MATCHES)); }
    void SelectMatch(MatchID_t selection) { bindingCommands.try_push(BindCmmd(selection)); }
    void CreateMatch() { bindingCommands.try_push(BindCmmd(BindCmmdCode::CREATE_MATCH)); }
    void StartMatch() { bindingCommands.try_push(BindCmmd()); }


    bool TrySendRequest(const CommandCode& cmmd) { return cmmdQueue.try_push(cmmd); }
    bool TryRecvNetworkMsg(std::shared_ptr<NetworkMsg>& msg) { return msgQueue.try_pop(msg); }


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
