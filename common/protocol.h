#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <exception>
#include <string>

#include "socket.h"


class Protocol {
    Socket skt;

public:
    // Constructor por referencia
    explicit Protocol(Socket&& skt);

    /*  Sends a string by first sending two bytes representing the string's size,
     *   followed by the string itself
     */
    void send_a_string(const std::string& name, bool& was_closed);

    // Send an integer using a single byte
    void send_a_int(const u_int8_t& box_id, bool& was_closed);

    // Receive an integer using a single byte
    u_int8_t recive_a_int(bool& was_closed);

    /*  Receives a string by first reading two bytes representing the string's size,
     *   followed by the string itself
     */
    std::string recive_a_string(bool& was_closed);
};
#endif
