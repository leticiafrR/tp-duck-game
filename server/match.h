#ifndef MATCH_H
#define MATCH_H
#include "../common/queue.h"
#include "../common/thread.h"

#include "monitorQueuesMsg.h"

typedef struct Message Message;  // desaparece con la integraciòn del protocolo
typedef struct Command Command;  // desaparece con la integraciòn del protocolo

class Match: public Thread {
private:
    size_t idClientCreator;
    int numberPlayers;
    MonitorQueuesMsg queuesMsg;
    Queue<Command> queueCmmd;

public:
    explicit Match(size_t idClientCreator);
    void run() override;
    void addClient(size_t idClient, Queue<Message>* queueMsg);
    void removeClient(size_t idClient);
};

#endif
