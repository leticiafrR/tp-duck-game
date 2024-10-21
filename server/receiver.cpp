#include "receiver.h"

ReceiverThread::ReceiverThread(MonitorMatches& matches, Socket sktPeer, size_t idClient):
        matches(matches), protocol(std::move(sktPeer)), idClient(idClient), myMatch(nullptr) {}

void ReceiverThread::run() {
    try {
        Lobby lobby();
        // lobby.asignMatch();
        SenderThread sender(myMatch, protocol, idClient);
        sender.start();
        receiveLoop();
        //
        sender.forceEnd();
        sender.join();
    } catch (const LibError& e) {

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

void ReceiverThread::receiveLoop() {}
void ReceiverThread::forceEnd() {}
