#include "receiver.h"

#include "../clientInfo.h"
#include "common/playerIdentifier.h"
#include "data/command.h"

ReceiverThread::ReceiverThread(std::shared_ptr<Queue<Command>> matchQueue, uint16_t clientID,
                               uint8_t playersPerConnection, ServerProtocol& protocol):
        matchQueue(matchQueue),
        clientID(clientID),
        playersPerConnection(playersPerConnection),
        protocol(protocol) {}

void ReceiverThread::run() {
    try {
        while (_keep_running) {
            Command cmmd = protocol.receiveCommand();
            if (cmmd.indexLocalPlayer < playersPerConnection) {
                cmmd.playerId = PlayerIdentifier::GeneratePlayerID(clientID, cmmd.indexLocalPlayer);
                matchQueue->push(cmmd);
            } else {
                std::cout << "Receiver Warning: The connection " << clientID
                          << " has send a command binded to a index of local player that is out of "
                             "the range of local players declared!"
                          << "\n";
                std::cout << cmmd.indexLocalPlayer << " not in range [0" << playersPerConnection - 1
                          << "]\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception in the receiver thread: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "ERROR: An unkown error was catched at the receiveLoop of the client with ID :"
                  << clientID << "\n";
    }
}

void ReceiverThread::kill() {
    /* Got here because the server is closing the
     * serving** (the aceptor: ended the match and it is killing all its clients) */

    /* Making the receiver loop to not keep running (we dont want to keep recieving commands while
     * the sender is ending) */
    stop();
}
