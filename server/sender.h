#ifndef SENDER_H
#define SENDER_H
#include <cstddef>

#include "../common/queue.h"
#include "../common/thread.h"

#include "match.h"
#include "serverProtocol.h"

class SenderThread: public Thread {
private:
    Queue<Message> mssgQueue;
    ServerProtocol& protocol;
    void recevierLoop();

public:
    explicit SenderThread(ServerProtocol& protocol);
    Queue<Message>* getMssgQueue();
    void run() override;
    void kill();

    ~SenderThread() override;
};

#endif
