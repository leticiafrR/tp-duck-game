#include "receiver.h"

ReceiverThread::ReceiverThread(Match& match, Socket&& sktPeer, PlayerID_t idClient):
        match(match),
        protocol(std::move(sktPeer)),
        sender(protocol, match, idClient),
        idClient(idClient) {}

void ReceiverThread::run() {
    try {

        PlayerInfo playerInfo;
        playerInfo.senderQueue = sender.getSenderQueue();
        bool playerConnected;
        playerInfo.nickName = protocol.receiveNickName(std::ref(playerConnected));

        if (match.loggInPlayer(idClient, playerInfo)) {
            sender.start();
            receiveLoop();
            sender.kill();
            sender.join();
        } else {
            protocol.sendResultOfJoining(false);
        }
    } catch (const LibError& e) {

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

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
    protocol.endConnection();
}
