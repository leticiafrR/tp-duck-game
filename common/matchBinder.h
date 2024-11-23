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

#define PRINT_MATCH_SELECTION(selection, connectionId)                                             \
    std::cout << "[ServerBinding]: Conection [" << (int)(connectionId) << "] tried to: "           \
              << ((selection) == (connectionId) ? "create a new match" : "join an existing match") \
              << "\n ";

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

                // std::cout << "[Client Binder]: result of joining/creating match received "
                //              "successfully: "
                //           << (msg->eCode == 0 ? "In the match!" : "couldnt join the match!")
                //           << " \n";
                if (msg->eCode == 0)
                    break;
                // else
                //     std::cout << "  Error code at joining match: " << msg->eCode << "\n";
            }
        }

        while (selection.matchSelection == localID) {
            matchSelections.pop();
            protocol.sendStartMatchIntention();
            auto msg = protocol.receiveResultStarting();
            msgQueue.push(msg);
            // std::cout << (msg->success ?
            //                       "Starting the match!" :
            //                       "Not enough players! You will have to wait for more players")
            //           << "\n";
            if (msg->success)
                break;
        }
    }

    static uint16_t ServerBind(MatchesMonitor& matches,
                               Queue<std::shared_ptr<MessageSender>>* clientQueue,
                               uint16_t connectionId, uint8_t& playersPerConnection,
                               ServerProtocol& protocol,
                               std::shared_ptr<Queue<Command>>& matchQueue) {
        // std::cout<<"BINDER: entrando al binding para el cliente: "<< connectionId<<"\n";

        uint16_t retMatchID = REFRESH;
        ClientInfo clientInfo;
        try {
            auto _baseNickname = protocol.receiveNickName();
            // std::cout<< "Binder: received the base nickname: "<< _baseNickname <<"\n";
            clientInfo.baseNickname = _baseNickname;
            clientInfo.connectionId = connectionId;

            protocol.sendLocalId(connectionId);
            // std::cout << "BINDER:se piden las av matches al monitor\n";
            auto avMatches = matches.getAvailableMatches();
            // std::cout << "BINDER: se obtuvieron las av matches del monitor\n";
            protocol.sendAvailableMatches(avMatches);


            while (retMatchID == REFRESH) {

                MatchSelection selection = protocol.receiveMatchSelection();
                if (selection.matchSelection == REFRESH) {
                    protocol.sendAvailableMatches(matches.getAvailableMatches());
                } else {
                    // PRINT_MATCH_SELECTION(selection.matchSelection, connectionId)
                    clientInfo.playersPerConnection = selection.playersPerConection;
                    uint8_t eCode = 0;
                    std::shared_ptr<Queue<Command>> returnQueue = matches.tryJoinMatch(
                            selection.matchSelection, clientQueue, clientInfo, eCode);

                    if (eCode == 0) {  // success!
                        // setting the target values received:
                        playersPerConnection = selection.playersPerConection;
                        matchQueue = returnQueue;

                        retMatchID = selection.matchSelection;
                    } else {
                        clientInfo.playersPerConnection = 0;
                    }
                    protocol.sendResultOfJoining(eCode);
                }
            }

            if (retMatchID == connectionId) {
                bool matchStarted = false;
                while (!matchStarted) {
                    protocol.receiveStartMatchIntention();

                    matchStarted = matches.tryStartMatch(retMatchID);
                    // std::cout << "Match [ID: " << retMatchID << "] starting result: "
                    //           << (matchStarted ? "Succes!" : "Failure! (Not enough players)")
                    //           << "\n";
                    protocol.sendStartMatchResult(matchStarted);
                }
            }
            return retMatchID;
        } catch (const LibError& err) {
            if (retMatchID != REFRESH)
                matches.forceEndMatch(retMatchID);

        } catch (const ConnectionFailed& err) {
            if (retMatchID != REFRESH)
                matches.forceEndMatch(retMatchID);
        } catch (const std::exception& e) {
            std::cerr << "ERROR at ServerBind to the client " << connectionId << ": " << e.what()
                      << std::endl;
        } catch (...) {
            std::cout << "Error. There was an unknown exception in the sender thread while "
                         "making the match bindng.\n";
        }
        // invalid match ID
        return 0;
    }


    MatchBinder() = delete;
    ~MatchBinder() = delete;
};
#endif
