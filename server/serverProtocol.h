#ifndef SERVERPROTOCOL_H
#define SERVERPROTOCOL_H

#include <string>
#include <utility>

#include "../common/dataTransferObjects.h"
#include "../common/protocolAssistant.h"
#include "../common/socket.h"

class ServerProtocol {
private:
    Socket skt;
    ProtocolAssistant assistant;

public:
    // Constructor
    explicit ServerProtocol(Socket&& skt);

    /* Send the result of trying to joing the match. If the connection with the client has been
     * detected lost it throws an exeption*/
    void sendResultOfJoining(const bool& success);


    /* Receives through the socket  the player's name. If the connection with the client has been
     * detected lost it throws an exeption*/
    std::string receiveNickName();

    // BEGGINING OF A MATCH
    /* Sends to the client a message with the ids of the participants of the match, their nickName,
     * and the number of skin assigned to each player ( K:id, V:{nickname, skinNumber} ), this is
     * the information related to the start of the whole match*/
    void sendMatchStartSettings(MatchStartSettingsDto matchStartSettings);

    // BEGINING OF A GAME
    void sendGameStartSettings(GameStartSettingsDto gameStartSettings);

    // DURING A GAME
    /* Receives through the socket the command (to apply to its player in the current game) and sets
     * the boolean received*/
    Command receiveCommand();

    /* Sends an update of the world of the current game: changes regarding the state of the world*/
    void sendGameUpdate(Snapshot update);

    // RECOUNT OF GAMES
    void sendGamesRecount(GamesRecountDto gamesRecount);

    // END OF A MATCH
    void sendMatchWinner(PlayerID_t finalWinner);

    void endConnection();
};

#endif
