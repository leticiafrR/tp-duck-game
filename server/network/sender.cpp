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
    PlayerID_t matchID =
            MatchBinder::ServerBind(matches, &senderQueue, playerID, protocol, matchQueue);
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
        std::cerr << "Exception in the sender thread (sendLoop): " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Error. There was an unexpected exception in the sender Thread.\n";
    }
}

void SenderThread::kill() {
    if (!_joinedAMatch) {
        protocol.endConnection();
    }
}

SenderThread::~SenderThread() {
    // try {
    //     if (_is_alive) {
    //         protocol.endConnection();
    //         join();
    //     }
    // } catch (...) {}
}
