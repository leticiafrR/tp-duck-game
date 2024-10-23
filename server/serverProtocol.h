#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <list>
#include <string>

#include "../common/dataMatch.h"
#include "../common/dataMove.h"
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

    // Send the connection status: Indicate whether the client successfully joined and if it is
    // still connected.
    void SendConectionStatus(const bool& ok, bool& isConnected);

    // Send the final status: Indicate whether the client won or lost.
    void SendFinalStatus(const bool& won, bool& isConnected);

    // Receive a message from the client.
    void Receive(bool& isConnected);  // Todavia no tiene un uso

    //
    void SendMatch(const size_t& matchID, const uint8_t& quantityP, const uint8_t& maxP,
                   bool& isConnected);

    //
    void SendBackGround(const uint8_t& backgroundID);

    // Receive the player's name
    std::string ReceiveNickName(bool& isConnected);

    // Receive a move message.
    dataMove ReceiveAMove(bool& isConnected);

    // Receive a match
    dataMatch ReceiveAMatch(bool& isConnected);

    // Send matches list
    void SendMatches(const std::list<dataMatch>& matches,
                     bool& isConnected);  // Asumo que como parametro va una lista C++ pero espero
                                          // confirmacion

    // Receive a client: the nickname and whether the client wants to open a new match or join an
    // existing one.
    dataMatch ReceiveAClient(bool& isConnected);
};

#endif
