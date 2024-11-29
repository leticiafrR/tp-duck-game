#include "Receiver.h"

#include <iostream>

#include "data/errorCodesJoinMatch.h"

#define THREAD_KILLED_TO_CLOSE_CLIENT_APP \
    "Client killed communication threads to orderly close the client application."
#define THREAD_KILLED_SERVER_DISCONNECTED                                                       \
    "Communication threads to the server killed due to detecting the server disconnection (so " \
    "don't have threads starving)"

#define NEW_MATCH 0
#define NON_CONCRETE_SELECTION_OF_MATCH 0

/*     ----------------public methods----------------     */

Receiver::Receiver(ClientProtocol& protocol, Queue<std::shared_ptr<NetworkMsg>>& msgQueue,
                   Queue<Command>& cmmdQueue, const std::string& name,
                   Queue<std::optional<MatchSelection>>& matchSelections,
                   std::atomic<uint16_t>& localID):
        protocol(protocol),
        msgQueue(msgQueue),
        sender(protocol, cmmdQueue),
        name(name),
        matchSelections(matchSelections),
        localID(localID) {}

void Receiver::run() {
    if (!bind())
        return;
    sender.start();
    receiveLoop();
    sender.kill();
    sender.join();
    _is_alive = false;
}

void Receiver::receiveLoop() {
    try {
        while (_keep_running) {
            std::shared_ptr<NetworkMsg> msg = protocol.receiveMessage();
            msgQueue.push(msg);
        }
    } catch (const ClosedQueue& q) {
        std::cerr << "[Receiver Thread]: (catch closed queue) " << THREAD_KILLED_TO_CLOSE_CLIENT_APP
                  << std::endl;
    } catch (const ConnectionFailed& c) {
        std::cerr << "[Receiver Thread]: " << THREAD_KILLED_SERVER_DISCONNECTED << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[Receiver Thread]: exception caught: " << e.what() << std::endl;
    }
}

void Receiver::kill() {
    msgQueue.close();
    protocol.endConnection();
}

/*     ----------------private methods----------------     */

bool Receiver::bind() {
    try {
        setClientProfile();
        msgQueue.push(protocol.receiveAvailableMatches());

        MatchSelection finalSelection;
        finalSelection.matchSelection = NON_CONCRETE_SELECTION_OF_MATCH;

        while (finalSelection.matchSelection == NON_CONCRETE_SELECTION_OF_MATCH) {
            MatchSelection actualSelection = getActualSelection();
            protocol.sendMatchSelection(actualSelection);

            if (actualSelection.matchSelection == NON_CONCRETE_SELECTION_OF_MATCH) {
                msgQueue.push(protocol.receiveAvailableMatches());
            } else {
                auto msg = protocol.receiveResultJoining();
                msgQueue.push(msg);
                if (msg->eCode == E_CODE::NONE)
                    finalSelection = actualSelection;
            }
        }
        clientHostStartMatch(finalSelection.matchSelection);
        return true;
    } catch (const ConnectionFailed& c) {
        std::cerr << THREAD_KILLED_SERVER_DISCONNECTED << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error caught at receiver thread while binding: " << e.what() << std::endl;
    }
    return false;
}

MatchSelection Receiver::getActualSelection() {
    std::optional<MatchSelection> opSelection = matchSelections.pop();
    if (opSelection.has_value()) {
        if (opSelection->matchSelection == NEW_MATCH)
            opSelection->matchSelection = localID;
        return opSelection.value();
    }
    // if the optional didnt had a value is a non concrete selection
    MatchSelection selection;
    selection.matchSelection = NON_CONCRETE_SELECTION_OF_MATCH;
    return selection;
}

void Receiver::setClientProfile() {
    protocol.sendNickname(name);
    localID = protocol.receiveLocalID();
    std::cout << "[Receiver]: Got the local id: " << localID << std::endl;
}

void Receiver::clientHostStartMatch(uint16_t matchID) {
    while (matchID == localID) {
        matchSelections.pop();
        protocol.sendStartMatchIntention();
        auto msg = protocol.receiveResultStarting();
        msgQueue.push(msg);
        if (msg->success)
            break;
    }
}
