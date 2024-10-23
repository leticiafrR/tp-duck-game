#ifndef MATCH_H
#define MATCH_H
#include "../common/queue.h"
#include "../common/thread.h"

#include "monitorQueuesMsg.h"

typedef struct Message Message;  // desaparece con la integraciòn del protocolo
typedef struct Command Command;  // desaparece con la integraciòn del protocolo

class Match: public Thread {
private:
    size_t idClientCreator;  // cppcheck-suppress unusedStructMember
    int numberPlayers;       // cppcheck-suppress unusedStructMember
    MonitorQueuesMsg queuesMsg;
    Queue<Command> commandQueue;

public:
    explicit Match(size_t idClientCreator);
    void run() override;
    // returns a boolean that indicating if the client was succesfully added
    // some reasons why the match wouldnt be able to add the client are:
    // the match already started
    // the limit of participants has been reached
    // the match has been ended because the client creator if it lost conection?
    // this boolean wont be enough to expresss this different reasons
    bool addClient(size_t idClient, Queue<Message>* queueMsg);
    void removeClient(size_t idClient);
    Queue<Command>& getCommandQueue();
};

#endif
