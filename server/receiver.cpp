#include "receiver.h"

ReceiverThread::ReceiverThread(PlayerID_t idClient, Match& match, ServerProtocol& protocol):
        match(match), idClient(idClient), protocol(protocol) {}

void ReceiverThread::run() {
    try {
        receiveLoop();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "ERROR: An unkown error was catched at the receiveLoop of the client with ID :"
                  << idClient << "\n";
    }
}

void ReceiverThread::receiveLoop() {
    try {
        while (_keep_running) {
            Command cmmd = protocol.receiveCommand();
            cmmd.playerId = idClient;
            match.pushCommand(cmmd);
        }
    } catch (const ConnectionFailed& c) {

        // the conexion is failing becasuse the client is dead (and the sender will notice that too)
        // and it will end the conexion (it it hasnt done that ) or because literally the sender is
        // who ended the conexion with the client.
        // or even if the match is over and it has closed our connexion before we fell into push a
        // command
    } catch (const LibError& e) {

    } catch (const ClosedQueue& q) {
        // got here because the queue has been closed by the match.
        //  nothing to do.
    }
}

void ReceiverThread::kill() {
    /* Got here because the server is closing the
     * serving** (the aceptor: ended the match and it is killing all its clients) */

    /* Making the receiver loop to not keep running (we dont want to keep recieving commands while
     * the sender is ending) */
    stop();
}

/* if the match has naturally ended it will close the connection of all its clients, this would
 * cause the sender to get blocked trying to make a pop in its response queue .*/
/* The sender needs the receiver to fail so it kills the sender properly (closing its queue)*/
