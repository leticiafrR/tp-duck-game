#ifndef PROTOCOL_ASSISTANT_H
#define PROTOCOL_ASSISTANT_H

#include <cstdint>  //para enteros de tamaño exacto
#include <stdexcept>
#include <string>

#include <arpa/inet.h>

#include "common/liberror.h"

#include "Vector2D.h"
#include "socket.h"

struct BrokenProtocol: public std::runtime_error {
    BrokenProtocol():
            std::runtime_error(
                    "ERROR: the other point of the connection has broken the protocol!") {}
};

struct ConnectionFailed: public std::runtime_error {
    ConnectionFailed(): std::runtime_error("Connection with the other endpoint was lost") {}
};

class ProtocolAssistant {

private:
    Socket& skt;
    bool wasClosed = false;

    void checkShipping(int cantBytes);

public:
    explicit ProtocolAssistant(Socket& skt);


    // envia por el socket el mensaje con el formato esperado para un string: (1byte:largo del
    // mensaje)
    void sendString(const std::string&);
    // recibe del socket un mensaje con el formato esperado
    std::string receiveString();


    // Envia en un byte el numero indicado
    void sendNumber(uint8_t);
    // Recibe un byte con un numero entero
    uint8_t receiveNumberOneByte();


    void sendNumber(uint32_t);
    uint32_t receiveNumberFourBytes();

    void sendNumber(uint16_t);
    uint16_t receiveNumberTwoBytes();


    // Send a float
    void sendFloat(const float& fl);
    // Receive a float
    float receiveFloat();


    void sendVector2D(const Vector2D& vector);
    Vector2D receiveVector2D();

    void sendBoolean(bool);
    bool receiveBooelan();
};
#endif
