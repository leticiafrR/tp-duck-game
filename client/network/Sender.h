#ifndef SENDER_H
#define SENDER_H
#include "common/queue.h"
#include "common/thread.h"

#include "ClientProtocol.h"

class Sender: public Thread {
private:
    ClientProtocol& protocol;
    Queue<Command>& cmmdQueue;

public:
    Sender(ClientProtocol& protocol, Queue<Command>& cmmdQueue);
    void run() override;
    void kill();
};
#endif
