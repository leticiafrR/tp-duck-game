#ifndef MONITOR_QUEUES_MSG_H
#define MONITOR_QUEUES_MSG_H
#include <cstddef>
#include <map>

#include "../common/queue.h"

typedef struct Message Message;  // desaparece con la integraciòn del protocolo


class MonitorQueuesMsg {
private:
    std::map<size_t, Queue<Message>*> queuesMsg;  // cppcheck-suppress unusedStructMember
    std::mutex mtx;

public:
    void addQueueMsg(size_t idClient, Queue<Message>* queueMsg);
    void removeQueueMsg(size_t idClient);
    void broadcast(const Message& msg);

    // not copyable
    MonitorQueuesMsg(const MonitorQueuesMsg&) = delete;
    MonitorQueuesMsg& operator=(const MonitorQueuesMsg&) = delete;
};

#endif
