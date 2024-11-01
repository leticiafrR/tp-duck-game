#include "sender.h"


SenderThread::SenderThread(ServerProtocol& protocol, Match& match, PlayerID_t idClient):
        senderQueue(MAX_MESSAGES), protocol(protocol), match(match), idClient(idClient) {}

Queue<std::shared_ptr<ClientMessage>>* SenderThread::getSenderQueue() { return &senderQueue; }

// as the sender is started only once the client could join a match  we communicate it
void SenderThread::run() {
    try {
        if (protocol.sendResultOfJoining(true)) {
            sendLoop();
        }
    } catch (const ClosedQueue& e) {
        /* graceful shutdown! */
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    match.loggOutPlayer(idClient);
}

void SenderThread::sendLoop() {
    while (_keep_running) {
        auto message = senderQueue.pop();
        if (!message->sendMyself(std::ref(protocol))) {
            stop();
        }
    }
}

void SenderThread::kill() { senderQueue.close(); }

// 1 donde comunicar que se terminò una ronda o que una nueva esta inciiando y tambien comunicar el
// seteo de esta nueva ronda (mapa)
