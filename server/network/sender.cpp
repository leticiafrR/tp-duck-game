#include "sender.h"

#include "common/matchBinder.h"

#include "messageSender.h"
#include "receiver.h"

SenderThread::SenderThread(Socket&& sktPeer, MatchesMonitor& matches, PlayerID_t playerID):
        matches(matches),
        senderQueue(MAX_MESSAGES),
        protocol(std::move(sktPeer)),
        playerID(playerID) {}


void SenderThread::run() {

    std::shared_ptr<Queue<Command>> matchQueue;
    PlayerID_t matchID = MatchBinder::bind(matches, &senderQueue, playerID, protocol, matchQueue);
    if (matchID == 0) {
        return;
    }
    _joinedAMatch = true;
    ReceiverThread receiver(playerID, matchQueue, protocol);
    receiver.start();
    sendLoop(matchID);
    receiver.join();
}

void SenderThread::sendLoop(PlayerID_t matchID) {
    try {
        while (_keep_running) {
            auto messageSender = senderQueue.pop();
            messageSender->execute(std::ref(protocol));
        }

    } catch (const ConnectionFailed& c) {
        matches.logOutPlayer(matchID, playerID);
    } catch (const LibError& e) {
        matches.logOutPlayer(matchID, playerID);
    } catch (const ClosedQueue& q) {

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cout << "Error. There was an unexpected exception in the sender Thread.\n";
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
