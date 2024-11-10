#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "../common/queue.h"
#include "../common/thread.h"
#include "../data/command.h"

#include "DataMatch.h"
#include "dataReceive.h"
#include "receiver.h"
#include "sender.h"
class Client: public Thread {
private:
    ClientProtocol protocol;
    Queue<DataRecieve>& updates;
    Queue<Command>& commands;
    DataMatch& actualMatch;
    Receiver recv;
    Sender send;
    void updateMatchChanges();
    bool WasClientFinished(const bool& gameEnded);

public:
    Client(const std::string& hostname, const std::string& srvname, Queue<DataRecieve>& upd,
           Queue<Command>& com, DataMatch& match, const std::string& nickname);
    void run() override;
    void shutdown();
};
#endif
