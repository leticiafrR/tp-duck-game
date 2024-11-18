#ifndef MATCH_BINDER_H
#define MATCH_BINDER_H

#include <exception>
#include <memory>

#include "client/network/ClientProtocol.h"
#include "data/dataMatch.h"
#include "data/id.h"
#include "server/matchesMonitor.h"
#include "server/network/serverProtocol.h"

#include "queue.h"

#define REFRESH 0

class MessageSender;  // not used


class MatchBinder {
public:
    static void BindClient(std::atomic<MatchID_t>& matchSelection, ClientProtocol& protocol,
                           Queue<std::shared_ptr<NetworkMsg>>& msgQueue) {

        while (matchSelection == REFRESHED_ID_CODE) {
            msgQueue.push(protocol.receiveAvailableMatches());
        }

        std::shared_ptr<NetworkMsg> msg = protocol.receiveResultJoining();
        msgQueue.push(msg);
        if (!dynamic_pointer_cast<ResultJoining>(msg)->joined) {
            BindClient(matchSelection, protocol, msgQueue);
        }
    }

    // returns an ID = 0 if the client didnt join a match
    static PlayerID_t bind(MatchesMonitor& matches,
                           Queue<std::shared_ptr<MessageSender>>* senderQueue, PlayerID_t playerID,
                           ServerProtocol& protocol, std::shared_ptr<Queue<Command>>& matchQueue) {
        PlayerID_t matchID = REFRESH;
        try {
            PlayerInfo playerInfo{protocol.receiveNickName(), senderQueue};
            protocol.sendIdentification(playerID);
            protocol.sendAvailableMatches(matches.getAvailableMatches());
            PlayerID_t selection;
            while (matchID == REFRESH) {
                selection = protocol.receiveMatchSelection();
                if (selection != REFRESH) {
                    std::shared_ptr<Queue<Command>> commandQueue =
                            matches.tryJoinMatch(selection, playerID, playerInfo);
                    if (commandQueue != nullptr) {
                        matchQueue = commandQueue;
                        matchID = selection;
                        protocol.sendResultOfJoining(true);
                    } else {
                        protocol.sendResultOfJoining(false);
                    }
                } else {
                    protocol.sendAvailableMatches(matches.getAvailableMatches());
                }
            }
            if (matchID == playerID) {
                bool matchStarted = false;
                while (!matchStarted) {
                    protocol.receiveStartMatchIntention();
                    matchStarted = matches.tryStartMatch(matchID);
                    protocol.sendStartMatchResult(matchStarted);
                }
            }
            return matchID;
        } catch (const LibError& err) {
            if (matchID != REFRESH)
                matches.forceEndMatch(matchID);

        } catch (const ConnectionFailed& err) {
            if (matchID != REFRESH)
                matches.forceEndMatch(matchID);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        } catch (...) {
            std::cout << "Error. There was an unexpected exception in the sender thread while "
                         "making the match bindng.\n";
        }
        return REFRESH;
    }

    MatchBinder() = delete;
    ~MatchBinder() = delete;
};
#endif
