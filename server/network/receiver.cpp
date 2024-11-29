#include "receiver.h"

#include "../clientInfo.h"
#include "common/playerIdentifier.h"
#include "data/command.h"

#define CLIENT_DISCONNECTED_THREAD_KILLED \
    "Communication thread killed when it was identified that the client was disconnected"
#define MATCH_OVER_KILLED_PARTICIPANTS                                                           \
    "Communication thread killed when identified client was communicating with a already ended " \
    "match"

ReceiverThread::ReceiverThread(MatchesMonitor& matches, std::shared_ptr<Queue<Command>> matchQueue,
                               const MatchSelection& matchSelection, uint16_t connectionId,
                               ServerProtocol& protocol):
        matches(matches),
        matchQueue(matchQueue),
        matchSelection(matchSelection),
        connectionId(connectionId),
        protocol(protocol) {}

void ReceiverThread::run() {
    try {
        while (_keep_running) {
            Command cmmd = protocol.receiveCommand();
            if (cmmd.indexLocalPlayer < matchSelection.playersPerConection) {
                cmmd.playerId =
                        PlayerIdentifier::GeneratePlayerID(connectionId, cmmd.indexLocalPlayer);
                matchQueue->push(cmmd);
            }
        }
    } catch (const ClosedQueue& q) {
        std::cerr << "[Receiver Thread " << connectionId << "]: " << MATCH_OVER_KILLED_PARTICIPANTS
                  << std::endl;
        return;
    } catch (const ConnectionFailed& c) {
        std::cerr << "[Receiver Thread " << connectionId
                  << "]: " << CLIENT_DISCONNECTED_THREAD_KILLED << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[Receiver Thread " << connectionId << "]: Exception caught :" << e.what()
                  << std::endl;
    }
    matches.logOutClient(matchSelection.matchSelection, connectionId);
}
