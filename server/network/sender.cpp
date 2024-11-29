#include "sender.h"

#include "messageSender.h"
#include "receiver.h"

#define NON_CONCRETE_SELECTION_OF_MATCH 0
#define MAX_MESSAGES 100
// pero quien està cerrando la queue???? creo que solo la match
#define MATCH_ENDED_KILLED_PARTICIPANTS \
    "Communication thread killed when match removed the client as participant."
#define CLIENT_DISCONNECTED_THREAD_KILLED \
    "Communication thread killed when it was identified that the client was disconnected."
#define CLIENT_DISCONNECTED_WHILE_BINDING                                                     \
    "Communication thread killed when it was identified that the client was disconnected, "   \
    "specifically identified while binding it whith a match, if have created one it will be " \
    "ended and deleted."

SenderThread::SenderThread(Socket&& sktPeer, MatchesMonitor& matches, uint16_t connectionId):
        matches(matches),
        senderQueue(MAX_MESSAGES),
        protocol(std::move(sktPeer)),
        connectionId(connectionId) {}

void SenderThread::run() {
    std::shared_ptr<Queue<Command>> matchQueue = bind();
    if (matchQueue == nullptr) {
        return;
    }
    _joinedAMatch = true;
    ReceiverThread receiver(matches, matchQueue, finalSelection, connectionId, protocol);
    receiver.start();
    sendLoop();
    receiver.join();
}

void SenderThread::sendLoop() {
    try {
        while (_keep_running) {
            auto messageSender = senderQueue.pop();
            messageSender->execute(std::ref(protocol));
        }
    } catch (const ClosedQueue& q) {
        std::cerr << "[Sender Thread " << connectionId << "]: (catch closed queue)"
                  << MATCH_ENDED_KILLED_PARTICIPANTS << std::endl;
    } catch (const ConnectionFailed& c) {
        std::cerr << "[Receiver Thread " << connectionId
                  << "]: " << CLIENT_DISCONNECTED_THREAD_KILLED << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[Receiver Thread " << connectionId << "]:Exception caught :" << e.what()
                  << std::endl;
    }
}

std::shared_ptr<Queue<Command>> SenderThread::bind() {
    ClientInfo clientInfo;
    if (!setClientProfile(clientInfo))
        return nullptr;
    std::shared_ptr<Queue<Command>> finalMatchQueue;
    finalSelection.matchSelection = NON_CONCRETE_SELECTION_OF_MATCH;
    try {
        auto avMatches = matches.getAvailableMatches();
        protocol.sendAvailableMatches(avMatches);
        while (finalSelection.matchSelection == NON_CONCRETE_SELECTION_OF_MATCH) {
            MatchSelection actualSelection = protocol.receiveMatchSelection();
            if (actualSelection.matchSelection == NON_CONCRETE_SELECTION_OF_MATCH) {
                protocol.sendAvailableMatches(matches.getAvailableMatches());
            } else {
                clientInfo.playersPerConnection = actualSelection.playersPerConection;
                uint8_t eCode = 0;
                std::shared_ptr<Queue<Command>> matchQueue = matches.tryJoinMatch(
                        actualSelection.matchSelection, &senderQueue, clientInfo, eCode);
                if (eCode == 0) {
                    finalSelection = actualSelection;
                    finalMatchQueue = matchQueue;
                }
                protocol.sendResultOfJoining(eCode);
            }
        }
        hostClientStartMatch(finalSelection.matchSelection);
        return finalMatchQueue;
    } catch (const ClosedQueue& q) {
        std::cerr << "[Sender Thread " << connectionId << "]: (catch closed queue)"
                  << MATCH_ENDED_KILLED_PARTICIPANTS << std::endl;
        return nullptr;
    } catch (const ConnectionFailed& c) {
        std::cerr << "[Sender Thread " << connectionId << "]: " << CLIENT_DISCONNECTED_WHILE_BINDING
                  << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[Sender Thread " << connectionId << "]: Exception caught :" << connectionId
                  << e.what() << std::endl;
    }
    handleBindingInterruption();
    return nullptr;
}

void SenderThread::handleBindingInterruption() {
    if (finalSelection.matchSelection == connectionId) {
        matches.forceEndMatch(connectionId);
    }
}

void SenderThread::hostClientStartMatch(uint16_t matchID) {
    if (matchID == connectionId) {
        bool matchStarted = false;
        while (!matchStarted) {
            protocol.receiveStartMatchIntention();
            matchStarted = matches.tryStartMatch(connectionId);
            protocol.sendStartMatchResult(matchStarted);
        }
    }
}

bool SenderThread::setClientProfile(ClientInfo& clientInfo) {
    try {
        auto _baseNickname = protocol.receiveNickName();
        protocol.sendLocalId(connectionId);
        clientInfo.baseNickname = _baseNickname;
        clientInfo.connectionId = connectionId;
        return true;
    } catch (const ConnectionFailed& c) {
        std::cerr << "[Sender Thread " << connectionId << "]: " << CLIENT_DISCONNECTED_THREAD_KILLED
                  << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[Sender Thread " << connectionId << "]: Exception caugth: " << e.what()
                  << std::endl;
    }
    return false;
}

void SenderThread::kill() {
    if (!_joinedAMatch) {
        protocol.endConnection();
    }
}
