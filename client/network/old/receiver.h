#ifndef RECEIVER_H
#define RECEIVER_H
#include "common/queue.h"
#include "common/thread.h"

#include "clientProtocol.h"
#include "dataReceive.h"
class Receiver: public Thread {
private:
    ClientProtocol& protocol;
    Queue<DataRecieve>& updates;
    bool inGame = false;

public:
    Receiver(ClientProtocol& prot, Queue<DataRecieve>& upd);
    void run() override;
    ~Receiver() = default;
};
#endif
