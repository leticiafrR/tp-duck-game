#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include "protocol.h"
#include "socket.h"
#include <list>
#include <string>
// El nick name se envia cada vez que envia algo

class ServerProtocol : public Protocol {
    private:

    public:
// Constructor
    ServerProtocol(Socket&& skt);

// Send the connection status: Indicate whether the client successfully joined and if it is still connected.
    void SendConectionStatus(const bool& ok, bool& is_connected);

// Send the final status: Indicate whether the client won or lost.
    void SendFinalStatus(const bool& won, bool& is_connected);

// Receive a message from the client.
    void Receive(bool& is_connected); // Todavia no tiene un uso

// Receive a move message.
    Move ReceiveAMove(bool& is_connected);

// Receive a match
    Match ReceiveAMatch(bool& is_connected);

// Send matches list
    void SendMatches(const std::list<Match> matches, bool& is_connected); // Asumo que como parametro va una lista C++ pero espero confirmacion

// Receive a client: the nickname and whether the client wants to open a new match or join an existing one.
    Match ReceiveAClient(bool& is_connected);

}
#endif
