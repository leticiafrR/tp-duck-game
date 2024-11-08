#ifndef SENDER_H
#define SENDER_H
#include <string>

#include "../data/command.h"
#include "common/queue.h"
#include "common/thread.h"
#include "data/dataTransferObjects.h"

#include "clientProtocol.h"
class Sender: public Thread {
private:
    ClientProtocol& protocol;
    Queue<CommandCode>& commands;
    // std::string nickname;

public:
    explicit Sender(ClientProtocol& prot, Queue<CommandCode>& comm, const std::string& nickname);
    void run() override;
    ~Sender() = default;
};
#endif
