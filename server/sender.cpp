#include "sender.h"


SenderThread::SenderThread(ServerProtocol& protocol, Match& match, size_t idClient):
        mssgQueue(MAX_MESSAGES), protocol(protocol), match(match), idClient(idClient) {}

Queue<Message>* SenderThread::getQueueMessage() { return &mssgQueue; }

void SenderThread::run() {
    try {
        sendLoop();
    } catch (const ClosedQueue& e) {
        /**
         * graceful shutdown!
         */
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    match.loggOutPlayer(idClient);
}

void SenderThread::sendLoop() {
    // while (_keep_running) {
    //     SnapShoot snapShoot = mssgQueue.pop();
    //     if (!protocol.sendSnapShoot(snapShoot)) {
    //         stop();
    //     }
    // }
}
// method called by the receiver thread when the match is iver
void SenderThread::kill() {}
