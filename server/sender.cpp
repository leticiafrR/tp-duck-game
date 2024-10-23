#include "sender.h"


SenderThread::SenderThread(ServerProtocol& protocol):
       protocol(protocol) {}

Queue<Message>* SenderThread::getMssgQueue() {
        return &mssgQueue;
}