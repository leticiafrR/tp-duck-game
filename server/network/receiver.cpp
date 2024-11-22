#include "receiver.h"

#include "data/command.h"

ReceiverThread::ReceiverThread(PlayerID_t idClient, std::shared_ptr<Queue<Command>> matchQueue,
                               ServerProtocol& protocol):
        matchQueue(matchQueue), idClient(idClient), protocol(protocol) {}

void ReceiverThread::run() {
    try {
        while (_keep_running) {
            Command cmmd = protocol.receiveCommand();
            cmmd.playerId = idClient;
            matchQueue->push(cmmd);
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception in the receiver thread: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "ERROR: An unkown error was catched at the receiveLoop of the client with ID :"
                  << idClient << "\n";
    }
}

void ReceiverThread::kill() {
    /* Got here because the server is closing the
     * serving** (the aceptor: ended the match and it is killing all its clients) */

    /* Making the receiver loop to not keep running (we dont want to keep recieving commands while
     * the sender is ending) */
    stop();
}
