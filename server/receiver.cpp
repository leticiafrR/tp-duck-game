#include "receiver.h"

ReceiverThread::ReceiverThread(Match& match, Socket sktPeer, size_t idClient):
        match(match), protocol(std::move(sktPeer)), idClient(idClient), commandQueue(match.getCommandQueue()) {}

void ReceiverThread::run() {
    try {
        SenderThread sender (protocol);
        match.addClient(idClient, sender.getMssgQueue());

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

void ReceiverThread::receiveLoop() {
    
}
void ReceiverThread::forceEnd() {}
