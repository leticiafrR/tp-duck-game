#ifndef SERVERPROTOCOL_H
#define SERVERPROTOCOL_H

#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "common/protocolAssistant.h"
#include "common/socket.h"
#include "data/command.h"
#include "data/communicationCodes.h"
#include "data/dataTransferObjects.h"
#include "data/gameScene.h"
#include "data/snapshot.h"

struct BrokenProtocol: public std::runtime_error {
    BrokenProtocol():
            std::runtime_error("Error: server perceived that the client broke the protocol!") {}
};

class ServerProtocol {
private:
    Socket skt;
    ProtocolAssistant assistant;
    V_BTTM_TOP encodeVisibleBottomTopEdges(const std::set<VISIBLE_EDGES>&);
    V_RG_LF encodeVisibleRightLeftEdges(const std::set<VISIBLE_EDGES>&);

public:
    // Constructor
    explicit ServerProtocol(Socket&& skt);

    /* Send the result of trying to joing the match. If the connection with the client has been
     * detected lost it throws an exeption*/
    void sendResultOfJoining(bool success);

    PlayerID_t receiveTryJoinMatch();

    void sendActivesMatches(const std::vector<ActiveMatch>& activeMatches);

    /* Receives through the socket  the player's name. If the connection with the client has been
     * detected lost it throws an exeption*/
    std::string receiveNickName();

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
    // agregar lasers
    /* Sends an update of the world of the current game: changes regarding the state of the world*/
    void sendGameUpdate(const Snapshot& snapshot);

    /* Sends a boolean indicating of this is the final game of the current group of games*/
    void sendGameEndingStatus(bool finalGroupGame);

    // RECOUNT OF GAMES
    void sendGamesRecount(const GamesRecountDto& gamesRecount);

    // END OF A MATCH
    void sendMatchWinner(PlayerID_t finalWinner);

    void endConnection();
};

#endif
