#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint>
#include <exception>
#include <string>

#include "socket.h"


class ProtocolAssistant {
    Socket& skt;

public:
    // Constructor
    explicit ProtocolAssistant(Socket& skt);

    /*  Sends a string by first sending two bytes representing the string's size,
     *   followed by the string itself
     */
    void sendString(const std::string& name, bool& wasClosed);

    // Send an integer using a single byte
    void sendInt(const uint8_t& boxId, bool& wasClosed);

    // Receive an integer using a single byte
    uint8_t reciveInt(bool& wasClosed);

    /*  Receives a string by first reading two bytes representing the string's size,
     *   followed by the string itself
     */
    std::string reciveString(bool& wasClosed);

    // Send a float
    void ProtocolAssistant::SendFloat(const float& ang, bool& wasClosed);

    // Receive a float
    float ProtocolAssistant::ReceiveFloat(bool& wasClosed);

    // Send a float
    void ProtocolAssistant::SendSizet(const size_t& ang, bool& wasClosed);

    // Receive a float
    size_t ProtocolAssistant::ReceiveSizet(bool& wasClosed);
};
#endif
