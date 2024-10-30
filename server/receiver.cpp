#include "receiver.h"

ReceiverThread::ReceiverThread(Match& match, Socket&& sktPeer, PlayerID_t idClient):
        match(match),
        protocol(std::move(sktPeer)),
        sender(protocol, match, idClient),
        idClient(idClient) {}

void ReceiverThread::run() {

    try {
        // this could be a great place to ask the nickname

        /* If loggInPlayer returns true the client was added to the match successfully */
        if (match.loggInPlayer(idClient, sender.getSenderQueue())) {
            // once here the client has joined to a match that could have more than a round

            sender.start();
            receiveLoop();
            sender.kill();
            sender.join();
        } else {
            // this method should make the client know that the match was fulled
            // protocol.sendRejection();
        }

    } catch (const LibError& e) {

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

// here we know that the match has started-> whe only receive coomands to apply to a game
// me parece que tendrìa que ser llamado cada vez que
void ReceiverThread::receiveLoop() {
    while (_keep_running) {

        bool isConnected;
        Command cmmd = protocol.receiveCommand(std::ref(isConnected));

        if (!isConnected) {
            stop();
        } else {
            cmmd.playerID = idClient;
            match.pushCommand(idClient, cmmd);
        }
    }
}

// Meanwhile this method is only called by the acceptor thread, maybe the acceptor could do a
// readEndedMatches -> and then killing all the client threads of those matches
void ReceiverThread::kill() {
    /* Got here because ¿the match has naturally ended? or  ** because the server is closing the
     * serving** (the aceptor: ended the match and it is killing all its clients) */

    /* Making the receiver loop to not keep running (we dont want to keep recieving commands while
     * the sender is ending) */
    stop();

    if (sender.is_alive()) {
        /* closing its queue */
        sender.kill();
        /*wait for all the left snapshoots to be send */
        sender.join();
    }
    /* Ending all the connection with the client */
    protocol.endConnection();
}
