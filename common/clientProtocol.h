#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>

#include <match.h>
#include <stdint.h>

#include "protocol.h"
#include "socket.h"

typedef enum: uint8_t {
    NEW_GAME = 1,
    JOIN_A_GAME,
    CANT_JOIN,
    MOVEMENT,
} MESSAGE_TYPE;

typedef enum: uint8_t {
    UP = 1,
    RIGHT,
    LEFT,
    DOWN,
    KEY_ON,
    KEY_OFF,
} KEYS;

class ClientProtocol: public Protocol {
private:
public:
    // Constructor
    ClientProtocol(Socket&& skt);

    // Send a request to open a new game
    void SendNewGame(bool& isConnected);

    // Send a request to join in a exiting game
    void JoinGame(bool& isConnected);

    // Send a move: Send a message with 4 as first byte ( that indicate that is a move message)
    // then send the movment id
    void SendMove(const uint8_t& keyId, bool& isConnected);

    // Send key state: Send whether the key is pressed (on) or released (off), and which key it is.
    void SendKeyHeld(const bool& keyOn, const uint8_t& keyId, bool& isConnected);

    // Receive matches list
    std::list<Match> ReceiveMatches(bool& isConnected);
};
#endif
