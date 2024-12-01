#ifndef CLIENT_H
#define CLIENT_H

#include <memory>
#include <string>
#include <utility>

#include "common/queue.h"

#include "ClientProtocol.h"
#include "Receiver.h"
// #include "data/snapshot.h"

#include "data/command.h"
#include "data/matchSelection.h"
#include "data/networkMsg.h"


#define MAX_MESSAGES 100
#define MAX_COMMANDS 100
#define DEFAULT_LOCAL_PLAYERS 1

struct ServerUnavailable: public std::runtime_error {
    ServerUnavailable(): std::runtime_error("Server connection unavailable") {}
};

class Client {
private:
    ClientProtocol protocol;
    std::atomic<uint16_t> localID = 0;

    Queue<std::shared_ptr<NetworkMsg>> msgQueue;
    Queue<Command> cmmdQueue;

    Queue<std::optional<MatchSelection>> matchSelections;

    std::unique_ptr<Receiver> receiver;

public:
    Client(const char* servname, const char* hostname, const std::string& name):
            protocol(std::move(Socket(hostname, servname))),
            msgQueue(MAX_MESSAGES),
            cmmdQueue(MAX_COMMANDS),
            receiver(std::make_unique<Receiver>(protocol, msgQueue, cmmdQueue, name,
                                                matchSelections, localID)) {
        receiver->start();
    }

    bool IsConnected() { return receiver->is_alive(); }

    void KillComunicationThreads() { receiver->kill(); }

    void JoinCommunicationThreads() { receiver->join(); }

    uint16_t GetLocalID() { return localID; }

    void Refresh() {
        // Empty selection to denote client dint take a match selection.
        std::optional<MatchSelection> selection{};
        matchSelections.try_push(selection);
    }

    void SelectMatch(uint16_t matchID, uint8_t playersPerConnection = DEFAULT_LOCAL_PLAYERS) {
        std::optional<MatchSelection> selection = MatchSelection(matchID, playersPerConnection);
        matchSelections.try_push(selection);
    }

    void CreateMatch(uint8_t playersPerConnection = DEFAULT_LOCAL_PLAYERS) {
        std::optional<MatchSelection> createSelection = MatchSelection(0, playersPerConnection);
        matchSelections.try_push(createSelection);
    }

    void StartMatch() {
        std::optional<MatchSelection> itentionStart{};
        matchSelections.try_push(itentionStart);
    }

    bool TrySendRequest(CommandCode code, uint8_t indexLocalPlayer = DEFAULT_LOCAL_PLAYERS - 1) {
        if (!IsConnected()) {
            std::cout << "No conectado en send!!!\n";
            throw ServerUnavailable();
        }

        Command command(code, indexLocalPlayer);
        return cmmdQueue.try_push(command);
    }

    template <typename NetworkMsgDerivedClass>
    bool TryRecvNetworkMsg(std::shared_ptr<NetworkMsgDerivedClass>& concretMsg) {

        if (!IsConnected()) {
            std::cout << "No conectado en recv!!!\n";
            throw ServerUnavailable();
        }

        std::shared_ptr<NetworkMsg> msg;
        if (msgQueue.try_pop(msg)) {
            concretMsg = dynamic_pointer_cast<NetworkMsgDerivedClass>(msg);
            return true;
        }
        return false;
    }

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    Client(Client&& other) = delete;
    Client& operator=(Client&& other) = delete;
};

#endif
