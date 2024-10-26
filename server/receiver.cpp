#include "receiver.h"

ReceiverThread::ReceiverThread(Match& match, Socket&& sktPeer, size_t idClient):
        match(match),
        protocol(std::move(sktPeer)),
        sender(protocol, match, idClient),
        idClient(idClient) {}

void ReceiverThread::run() {

    try {
        /* If loggInPlayer returns false the match has already started */
        if (match.loggInPlayer(idClient, sender.getQueueMessage())) {
            sender.start();
            receiveLoop();
            sender.kill();
            sender.join();
        }
    } catch (const LibError& e) {

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

void ReceiverThread::receiveLoop() {
    /*discomment whhen checked what does the protocol returns*/
    while (_keep_running) {
        /* dont forget to delete the part "= false" */
        bool client_alive = false;
        // Command cmmd = protocol.getCommand(std::ref(client_alive));
        if (!client_alive) {  // cppcheck-suppress knownConditionTrueFalse
            stop();
        }  // else {
        //     match.pushCommand(idClient, cmmd);
        // }
    }
}
// this method ends the comunication with the client making sure that the Sender thread finishes its
// execution (as long as the match producer of SnapShoots stops make boradcasts over this client)
// and cleaning the resources of it (join)
//  Respect of this thread it ends the execution of the receiveLoop by ending the conextion with the
//  client. The explicit call to ReceiverThread::join() has to be done
void ReceiverThread::kill() {
    /*
     * Got here because the match has naturally ended or  because the server is closing the serving
     * (killing the match): -first end the sender (if it is neeedt), only when it ends sending the
     * data that it has to: send end all comunication with the client
     */
    if (sender.is_alive()) {
        sender.kill();
        sender.join();
    }

    /*>
    mètodo del protocolo para cerrar la conexiòn
        skt_peer.shutdown(2);
        skt_peer.close();
    */
    // protocol.endConnection();
}
