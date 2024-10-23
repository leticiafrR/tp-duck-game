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
    Queue<Command> commandQueue;

public:
    explicit Match(size_t idClientCreator);
    void run() override;
    //returns a boolean that indicating if the client was succesfully added
    bool addClient(size_t idClient, Queue<Message>* queueMsg);
    void removeClient(size_t idClient);
    Queue<Command>& getCommandQueue();
};

#endif
