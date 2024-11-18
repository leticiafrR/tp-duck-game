#ifndef MATCH_BINDER_H
#define MATCH_BINDER_H

#include <exception>
#include <memory>

#include "client/network/ClientProtocol.h"
#include "client/network/bindCmmd.h"
#include "data/dataMatch.h"
#include "data/id.h"
#include "server/matchesMonitor.h"
#include "server/network/serverProtocol.h"

#include "queue.h"

#define REFRESH 0

class MessageSender;  // not used

class MatchBinder {
public:
    static void ClientBind(PlayerID_t id, Queue<std::shared_ptr<NetworkMsg>>& msgQueue,
                           Queue<BindCmmd>& bindingCommands, ClientProtocol& protocol) {

        msgQueue.push(protocol.receiveAvailableMatches());
        BindCmmd cmd;
        while (true) {
            cmd = bindingCommands.pop();
            if (cmd.code == BindCmmdCode::CREATE_MATCH) {
                cmd.selection = id;
            }

            // despues de recibir las availables matches siempre se envia la selecciòn (0 si
            // refresca, idclient si crea, idmatch si se une)
            protocol.sendMatchSelection(cmd.selection);
            if (cmd.code == BindCmmdCode::REFRESH_MATCHES) {
                msgQueue.push(protocol.receiveAvailableMatches());
            } else {
                auto msg = protocol.receiveResultJoining();
                msgQueue.push(msg);
                if (msg->joined) {
                    break;
                }
            }
        }

        while (cmd.code == BindCmmdCode::CREATE_MATCH) {
            bindingCommands.pop();
            protocol.sendStartMatchIntention();
            auto msg = protocol.receiveResultJoining();
            msgQueue.push(msg);
            if (msg->joined) {
                break;
            }
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
