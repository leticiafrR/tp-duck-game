#include "sender.h"

// pregunta, si es que un jugador puede pasar un tiempo ilimitado en un lobby, còmo se mata al
// cliente? -> cerrando su protocolo
SenderThread::SenderThread(Socket&& sktPeer, MatchesMonitor& matches, PlayerID_t idClient):
        matches(matches),
        senderQueue(MAX_MESSAGES),
        protocol(std::move(sktPeer)),
        idClient(idClient) {}

bool SenderThread::joinedAMatch() { return _joinedAMatch; }

void SenderThread::run() {
    // std::shared_ptr<Queue<Command>> matchQueue;

    // Lobby(matchesMonitor, std::ref(_joinedAMatch), IDPlayer, std::ref(senderQueue), protocol,
    // matchQueue); lobby.start() Looby.join()


    if (!_joinedAMatch) {
        return;
    }

    // ReceiverThread receiver(idClient, matchQueue , protocol);
    // receiver.start();
    // sendLoop(lobby.getMatchID());
    // receiver.join();
}

void SenderThread::sendLoop(uint32_t matchID) {
    try {
        while (_keep_running) {
            auto messageSender = senderQueue.pop();
            messageSender->execute(std::ref(protocol));
        }

    } catch (const ConnectionFailed& c) {

        // matchesMonitor.logOutPlayer(matchID, idClient);
        protocol.endConnection();

    } catch (const LibError& e) {

        // matchesMonitor.logOutPlayer(matchID, idClient);
        protocol.endConnection();

    } catch (const ClosedQueue& q) {
        // got here because the match has killed us (is the only one that closes this queue)
        // we dont have to either try to remove the Player off the match nor endTheConection
        // the messageSender->execute() that had that killer message has done it).
    } catch (...) {
        std::cout << "HUBO UN ERROR EN EL HILO SENDER!!\n";
    }
}

void SenderThread::kill() {
    if (!_joinedAMatch) {
        protocol.endConnection();
    }
}

// no es definitivo este bloque try-catch, solo era para asegurarme que no crashee el servidor
// (ya que si se lanza una excepciòn en un desructor los programas crashean)
SenderThread::~SenderThread() {
    try {
        if (_is_alive) {
            kill();
            join();
        }
    } catch (...) {
        std::cout << "ERROR: se atrapò un error en el destructor  del sender\n";
    }
}
