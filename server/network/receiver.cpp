#include "receiver.h"

#include "../clientInfo.h"
#include "common/playerIdentifier.h"
#include "data/command.h"

ReceiverThread::ReceiverThread(MatchesMonitor& matches, std::shared_ptr<Queue<Command>> matchQueue,
                               uint16_t matchID, uint16_t connectionId,
                               uint8_t playersPerConnection, ServerProtocol& protocol):
        matches(matches),
        matchQueue(matchQueue),
        matchID(matchID),
        connectionId(connectionId),
        playersPerConnection(playersPerConnection),
        protocol(protocol) {}

void ReceiverThread::run() {
    try {
        while (_keep_running) {
            Command cmmd = protocol.receiveCommand();
            if (cmmd.indexLocalPlayer < playersPerConnection) {
                cmmd.playerId =
                        PlayerIdentifier::GeneratePlayerID(connectionId, cmmd.indexLocalPlayer);
                matchQueue->push(cmmd);
            }
        }
    } catch (const ConnectionFailed& c) {
        matches.logOutClient(matchID, connectionId);
    } catch (const LibError& e) {
        matches.logOutClient(matchID, connectionId);

    } catch (const ClosedQueue& q) {
        std::cout << "[RECEIVER: " << connectionId << "] the match has closed its queue\n";
    } catch (const std::exception& e) {
        std::cerr << "Exception in the receiver thread: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "ERROR: An unkown error was catched at the receiveLoop of the client with ID :"
                  << connectionId << "\n";
    }
}
