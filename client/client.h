#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "../common/queue.h"
#include "../common/thread.h"
#include "../data/command.h"

#include "dataReceive.h"
#include "receiver.h"
#include "sender.h"
class Client {
private:
    ClientProtocol protocol;
    Queue<DataRecieve>& updates;
    Queue<CommandCode>& commands;
    Receiver recv;
    Sender send;
    void updateMatchChanges();
    bool WasClientFinished(const bool& gameEnded);

public:
    Client(const std::string& hostname, const std::string& srvname, Queue<DataRecieve>& upd,
           Queue<CommandCode>& com, const std::string& nickname);
    void run();
    void shutdown();
};
#endif
