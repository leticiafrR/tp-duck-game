#ifndef MATCH_BINDER_H
#define MATCH_BINDER_H


#include <exception>
#include <memory>
#include <optional>

#include "client/network/ClientProtocol.h"
#include "data/dataMatch.h"
#include "data/id.h"
#include "server/matchesMonitor.h"
#include "server/network/serverProtocol.h"

#include "queue.h"

#define REFRESH 0
#define NOT_ASSIGNED 0

class MessageSender;

class MatchBinder {
public:
    static void ClientBind(uint16_t localID, Queue<std::shared_ptr<NetworkMsg>>& msgQueue,
                           Queue<std::optional<MatchSelection>>& matchSelections,
                           ClientProtocol& protocol) {

        msgQueue.push(protocol.receiveAvailableMatches());
        MatchSelection selection;
        while (true) {
            std::optional<MatchSelection> opSelection = matchSelections.pop();
            if (opSelection.has_value()) {
                if (opSelection->matchSelection == NOT_ASSIGNED)
                    opSelection->matchSelection = localID;
                selection = opSelection.value();
            } else {
                // default
                selection.matchSelection = REFRESH;
            }
            protocol.sendMatchSelection(selection);

            if (selection.matchSelection == REFRESH) {
                msgQueue.push(protocol.receiveAvailableMatches());
            } else {
                auto msg = protocol.receiveResultJoining();
                msgQueue.push(msg);
                if (msg->eCode == 0)
                    break;
            }
        }

        while (selection.matchSelection == localID) {
            matchSelections.pop();
            protocol.sendStartMatchIntention();
            auto msg = protocol.receiveResultStarting();
            msgQueue.push(msg);
            if (msg->success)
                break;
        }
    }

    static uint16_t ServerBind(MatchesMonitor& matches,
                               Queue<std::shared_ptr<MessageSender>>* clientQueue,
                               uint16_t connectionId, uint8_t& playersPerConnection,
                               ServerProtocol& protocol,
                               std::shared_ptr<Queue<Command>>& matchQueue) {

        uint16_t retMatchID = REFRESH;
        ClientInfo clientInfo;
        try {
            auto _baseNickname = protocol.receiveNickName();
            clientInfo.baseNickname = _baseNickname;
            clientInfo.connectionId = connectionId;

            protocol.sendLocalId(connectionId);
            auto avMatches = matches.getAvailableMatches();
            protocol.sendAvailableMatches(avMatches);


            while (retMatchID == REFRESH) {
                MatchSelection selection = protocol.receiveMatchSelection();
                if (selection.matchSelection == REFRESH) {
                    protocol.sendAvailableMatches(matches.getAvailableMatches());
                } else {
                    clientInfo.playersPerConnection = selection.playersPerConection;
                    uint8_t eCode = 0;
                    std::shared_ptr<Queue<Command>> returnQueue = matches.tryJoinMatch(
                            selection.matchSelection, clientQueue, clientInfo, eCode);
                    if (eCode == 0) {
                        // setting the target values received:
                        playersPerConnection = selection.playersPerConection;
                        matchQueue = returnQueue;
                        retMatchID = selection.matchSelection;
                        matches.printMatchStatus(selection.matchSelection);
                    }
                    protocol.sendResultOfJoining(eCode);
                }
            }

            if (retMatchID == connectionId) {
                bool matchStarted = false;
                while (!matchStarted) {
                    protocol.receiveStartMatchIntention();
                    matchStarted = matches.tryStartMatch(retMatchID);
                    protocol.sendStartMatchResult(matchStarted);
                }
            }
            return retMatchID;
        } catch (const LibError& err) {
            if (retMatchID == connectionId) {
                matches.forceEndMatch(retMatchID);
            }

        } catch (const ConnectionFailed& err) {
            if (retMatchID == connectionId) {
                matches.forceEndMatch(retMatchID);
            }
        } catch (const std::exception& e) {
            std::cerr << "ERROR at ServerBind to the client " << connectionId << ": " << e.what()
                      << std::endl;
        } catch (...) {
            std::cout << "Error. There was an unknown exception in the sender thread while "
                         "making the match bindng.\n";
        }
        // no-existing match ID
        return 0;
    }


    MatchBinder() = delete;
    ~MatchBinder() = delete;
};
#endif
