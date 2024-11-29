#ifndef RECEIVER_H
#define RECEIVER_H

#include <memory>
#include <optional>
#include <string>

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
             Queue<std::optional<MatchSelection>>& matchSelections, std::atomic<uint16_t>& localID);

    void run() override;
    void kill();

private:
    void receiveLoop();
    MatchSelection getActualSelection();
    bool bind();
    void setClientProfile();
    void clientHostStartMatch(uint16_t matchID);
};


#endif
