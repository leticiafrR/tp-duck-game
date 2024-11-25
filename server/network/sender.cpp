#include "sender.h"

#include "common/matchBinder.h"

#include "messageSender.h"
#include "receiver.h"

SenderThread::SenderThread(Socket&& sktPeer, MatchesMonitor& matches, uint16_t connectionId):
        matches(matches),
        senderQueue(MAX_MESSAGES),
        protocol(std::move(sktPeer)),
        connectionId(connectionId) {}


void SenderThread::run() {

    std::shared_ptr<Queue<Command>> matchQueue;
    uint8_t playersPerConnection;
    uint16_t matchID = MatchBinder::ServerBind(matches, &senderQueue, connectionId,
                                               playersPerConnection, protocol, matchQueue);
    if (matchID == 0) {
        return;
    }
    _joinedAMatch = true;
    ReceiverThread receiver(matches, matchQueue, matchID, connectionId, playersPerConnection,
                            protocol);
    receiver.start();
    sendLoop();
    receiver.join();
    std::cout << "The client " << connectionId << "is dead (recogible)\n";
}

void SenderThread::sendLoop() {
    try {
        while (_keep_running) {
            auto messageSender = senderQueue.pop();
            messageSender->execute(std::ref(protocol));
        }

    } catch (const ConnectionFailed& c) {
    } catch (const LibError& e) {
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

SenderThread::~SenderThread() {}
