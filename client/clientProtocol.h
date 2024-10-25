#ifndef CLIENTPROTOCOL_H
#define CLIENTPROTOCOL_H

#include <cstdint>
#include <list>
#include <string>

#include <stdint.h>

#include "../common/dataMatch.h"
#include "../common/dataObject.h"
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

class ClientProtocol {
private:
    Socket skt;
    ProtocolAssistant assistant;

public:
    // Constructor
    explicit ClientProtocol(Socket&& skt);

    // Send a request to open a new game
    void SendNewGame(const std::string& name, bool& isConnected);

    // Send the nickname
    void SendName(const std::string& name, bool& isConnected);

    // Send a request to join in a exiting game
    void JoinGame(const std::string& name, bool& isConnected);

    // Send a move: Send a message with 4 as first byte ( that indicate that is a move message)
    // then send the movment id
    void SendMove(const std::string& name, const uint8_t& keyId, bool& isConnected);

    // Send key state: Send whether the key is pressed (on) or released (off), and which key it is.
    void SendKeyHeld(const std::string& name, const bool& keyOn, const uint8_t& keyId,
                     bool& isConnected);

    //
    dataMatch ReceiveMatch(bool& isConnected);

    //
    uint8_t ReceiveBackGround(bool& isConnected);

    //
    dataPlayer ReceiveAPlayer(bool& isConnected);

    // Receive matches list
    std::list<dataMatch> ReceiveMatches(bool& isConnected);
};
#endif
