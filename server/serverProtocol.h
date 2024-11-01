#ifndef SERVERPROTOCOL_H
#define SERVERPROTOCOL_H

#include <list>
#include <string>

#include "../common/command.h"
#include "../common/dataMatch.h"
#include "../common/dataObject.h"
#include "../common/protocolAssistant.h"
#include "../common/snapShoot.h"
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

    // Sends what is the player skin and the position
    void SendAObject(const dataObject& player, bool& isConnected);

    //
    void SendATransform(const Transform& transform, bool& isConnected);  // tiene que ser privado

    //
    void SendAWeapon(bool& isConnected);  // tiene que ser privado

    void SendADuck(const Duck& duck);  // tiene que ser privado

    // Receive the player's name
    std::string ReceiveNickName(bool& isConnected);

    /* The following methods had been commented (by me Andrea) because the conflict of working with
     * different structures (i have changed the names: dataMove/dataCommand -> Command,
     * dataMatch->SnapShoot), meanwhile i preffer to just comment this methods*/

    // // Receive a move message.
    // dataMove ReceiveAMove(bool& isConnected);

    // // Receive a match
    // dataMatch ReceiveAMatch(bool& isConnected);

    // // Send matches list
    // void SendMatches(const std::list<dataMatch>& matches,
    //                  bool& isConnected);  // Asumo que como parametro va una lista C++ pero
    //                  espero
    //                                       // confirmacion

    // // Receive a client: the nickname and whether the client wants to open a new match or join an
    // // existing one.
    // dataMatch ReceiveAClient(bool& isConnected);

    /*The following methods werent implemmented neigther by Candela nor me. But this is how i need
     * the API to be.*/

    // sets the value of `clientAlive` depending on whether the client was connected.
    Command receiveCommand(bool& clientAlive);

    // returns false if the message couldnt be send (ej the client has disconnected)
    bool sendSnapShoot(const SnapShoot& gameStatus);

    void endConnection();
    /*{
        skt_peer.shutdown(2);
        skt_peer.close();
    }*/
};

#endif