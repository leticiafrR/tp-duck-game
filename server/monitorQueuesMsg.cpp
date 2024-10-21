#include "monitorQueuesMsg.h"

void MonitorQueuesMsg::addQueueMsg(size_t idClient, Queue<Message>* queueMsg) {
    std::unique_lock<std::mutex> lock(mtx);
    queuesMsg[idClient] = queueMsg;
}

void MonitorQueuesMsg::removeQueueMsg(size_t idClient) {
    std::unique_lock<std::mutex> lock(mtx);
    queuesMsg.erase(idClient);
}

void MonitorQueuesMsg::broadcast(const Message& msg) {
    std::unique_lock<std::mutex> lock(mtx);
    for (auto pair: queuesMsg) {
        (pair.second)->try_push(msg);
    }
}

MonitorQueuesMsg::~MonitorQueuesMsg() { queuesMsg.clear(); }
