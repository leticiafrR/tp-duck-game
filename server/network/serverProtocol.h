#ifndef SERVERPROTOCOL_H
#define SERVERPROTOCOL_H

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "common/protocolAssistant.h"
#include "common/socket.h"
#include "data/command.h"
#include "data/communicationCodes.h"
#include "data/dataMatch.h"
#include "data/dataTransferObjects.h"
#include "data/gameScene.h"
#include "data/matchSelection.h"
#include "data/snapshot.h"

class ServerProtocol {
private:
    Socket skt;
    ProtocolAssistant assistant;
    V_BTTM_TOP encodeVisibleBottomTopEdges(const std::set<VISIBLE_EDGES>&);
    V_RG_LF encodeVisibleRightLeftEdges(const std::set<VISIBLE_EDGES>&);
    void sendPlayerUpdates(const std::unordered_map<PlayerID_t, PlayerEvent>& updates);
    void sendRaycastsEvents(const std::vector<InstantProjectileEventDto>& raycastsEvents);
    void sendCollectableDespawns(const std::vector<CollectableID_t>& collectableDespawns);
    void sendCollectableSpawns(const std::vector<CollectableSpawnEventDto>& collectableSpawns);
    void sendThrowableSpawns(
            const std::unordered_map<ThrowableID_t, ThrowableSpawnEventDto>& throwableSpawns);
    void sendThrowableDespawns(const std::vector<ThrowableID_t>& throwableDespawns);

public:
    explicit ServerProtocol(Socket&& skt);

    std::string receiveNickName();

    void sendLocalId(uint16_t connectionId);

    MatchSelection receiveMatchSelection();

    void sendResultOfJoining(uint8_t eCode);

    void sendAvailableMatches(const std::vector<DataMatch>& matches);

    void receiveStartMatchIntention();

    void sendStartMatchResult(bool success);


    // BEGGINING OF A MATCH
    /* Sends to the client a message with the ids of the participants of the match, their nickName,
     * and the number of skin assigned to each player ( K:id, V:{nickname, skinNumber} ), this is
     * the information related to the start of the whole match*/
    void sendMatchStartSettings(const MatchStartDto& matchStartDto);

    // BEGINING OF A GAME
    void sendGameStartSettings(const GameSceneDto& gameSceneDto);


    // DURING A GAME
    /* Receives through the socket the command (to apply to its player in the current game) and sets
     * the boolean received*/
    Command receiveCommand();

    /* Sends an update of the world of the current game: changes regarding the state of the world*/
    void sendGameUpdate(const Snapshot& snapshot);

    /* Sends a boolean indicating of this is the final game of the current group of games*/
    void sendGameEndingStatus(bool finalGroupGame);

    void sendGamesRecount(const GamesRecountDto& gamesRecount);

    // END OF A MATCH
    void sendMatchWinner(PlayerID_t finalWinner);

    void endConnection();

    // not copyable
    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;
};

#endif
