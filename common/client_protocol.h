#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include "protocol.h"
#include "socket.h"
#include <stdint.h> 
#include <string>
#include <match.h>

typedef enum : u_int8_t{
    NEW_GAME = 1,
    JOIN_A_GAME,
    CANT_JOIN,
    MOVEMENT,
} MESSAGE_TYPE;

typedef enum : u_int8_t{
    UP = 1,
    RIGHT,
    LEFT,
    DOWN,
    KEY_ON,
    KEY_OFF,
} KEYS;

class ClientProtocol : public Protocol {
    private:

    public:
// Constructor
    ClientProtocol(Socket&& skt);

// Send a request to open a new game
    void SendNewGame(bool& is_connected);

// Send a request to join in a exiting game
    void JoinGame(bool& is_connected);

// Send a move: Send a message with 4 as first byte ( that indicate that is a move message)
// then send the movment id
    void SendMove(const u_int8_t& key_id, bool& is_connected);

// Send key state: Send whether the key is pressed (on) or released (off), and which key it is.
    void SendKeyHeld(const bool& key_on, const u_int8_t& key_id, bool& is_connected);

// Receive matches list
    std::list<Match> ReceiveMatches(bool& is_connected);
};
#endif
