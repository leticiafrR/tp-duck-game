#ifndef SERVERPROTOCOL_H
#define SERVERPROTOCOL_H

#include <list>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "../common/command.h"
#include "../common/protocolAssistant.h"
#include "../common/socket.h"

typedef enum: uint8_t {
    NEW_GAME = 1,
    JOIN_A_GAME,
    ERROR_JOIN,
    ACTIVE_MATCHES,
    NAME,
    A_MATCH,
    MOVEMENT,
    EQUIPMENT,
    ATACK,
    FINAL_STATUS,

} MESSAGE_TYPE;

typedef enum: uint8_t {
    UP = 1,
    RIGHT,
    LEFT,
    DOWN,
    SHOOT,
    KEY_UP,
    KEY_DOWN,
} KEYS;

// El nick name se envia cada vez que envia algo

class ServerProtocol {
private:
    Socket skt;
    ProtocolAssistant assistant;

public:
    // Constructor
    explicit ServerProtocol(Socket&& skt);

    /* Send the result of trying to joing the match. Returns a boolean depending on whether the
     * player was still conected or not*/
    bool sendResultOfJoining(const bool& success);


    /* Receives through the socket  the player's name and sets the value of the boolean received
     * (isConnected)*/
    std::string receiveNickName(bool& isConnected);

    // BEGGINING OF A MATCH
    /* Sends to the client a message with the ids of the participants of the match, their nickName,
     * and the number of skin assigned to each player ( K:id, V:{nickname, skinNumber} ), this is
     * the information related to the start of the whole match*/
    bool sendMatchStartSettings(
            const std::unordered_map<int, std::tuple<PlayerID_t, std::string> >& skinsAssignation);

    // BEGINING OF A GAME
    //  OJO: CAMBIAR AL CORRECTO TIPADO DE LAS PLATAFORMAS DEL JUEGO
    bool sendGameStartSettings(const std::string& theme, std::vector<Transform>& gamePlatforms);

    // DURING A GAME
    /* Receives through the socket the command (to apply to its player in the current game) and sets
     * the boolean received*/
    Command receiveCommand(bool& clientAlive);

    /* Sends an update of the world of the current game: changes regarding the state of the world*/
    bool sendGameUpdate(const SnapShoot& update);

    // RECOUNT OF GAMES
    bool sendGamesRecount(const std::unordered_map<PlayerID_t, int>& results);

    // END OF A MATCH
    bool sendMatchResult(PlayerID_t finalWinner);

    void endConnection();
};

#endif

// desde el punto de vista del clientee:
/* Entonces el cliente recibirà al intentar unirse a una partida:
    -un mensaje del resultado de unirse a la partida (true-> exito, false-> fracaso)
    (en caso de que se haya podido ingresar a la partida)
    -un mensaje del inicio de la match: que comunica la asignaciòn de las skins (ids-> {nickname,
   skinNumber})
        /-un mensaje del inicio de un game: que comunica el nombre del fondo donde se lleva a cabo
          el nivel y las las plataformas de este
        /-actualizaciones durante un game: snapshoots

        -cada 5 partidas un listado con los games ganados por cada participante

    -un mensaje del final de toda la match: que comunica el id de jugador ganador.
*/
