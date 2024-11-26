#include "protocolAssistant.h"

#include <iostream>

ProtocolAssistant::ProtocolAssistant(Socket& skt): skt(skt) {}

void ProtocolAssistant::checkShipping(int cantBytes, const std::string& when) {
    if (cantBytes == 0) {
        std::cout << "[Protocol_assistant]:result of checking bytes is 0, when " << when
                  << ". The connion has been shuted down.\n";
        throw ConnectionFailed();
    }
}
void ProtocolAssistant::sendString(const std::string& cont) {
    uint16_t lenMessage = cont.size();
    lenMessage = htons(lenMessage);
    checkShipping(skt.sendall(&lenMessage, sizeof(uint16_t), &wasClosed), "sending a string");
    checkShipping(skt.sendall(cont.data(), cont.size(), &wasClosed), "sending a string");
}

std::string ProtocolAssistant::receiveString() {
    uint16_t lenMessage;
    checkShipping(skt.recvall(&lenMessage, sizeof(lenMessage), &wasClosed), "receiving a string");
    lenMessage = ntohs(lenMessage);
    std::string buffer(lenMessage, '\0');
    checkShipping(skt.recvall(&buffer[0], lenMessage, &wasClosed), "receiving a string");
    return buffer;
}

void ProtocolAssistant::sendNumber(uint8_t number) {
    checkShipping(skt.sendall(&number, sizeof(number), &wasClosed), "sending a number 1 byte");
}

uint8_t ProtocolAssistant::receiveNumberOneByte() {
    uint8_t number;
    checkShipping(skt.recvall(&number, sizeof(number), &wasClosed), "receiving a number one byte");
    return number;
}

void ProtocolAssistant::sendNumber(uint32_t number) {
    checkShipping(skt.sendall(&number, sizeof(number), &wasClosed), "sending a number 4 bytes");
}

uint32_t ProtocolAssistant::receiveNumberFourBytes() {
    uint32_t number;
    checkShipping(skt.recvall(&number, sizeof(number), &wasClosed),
                  "receiving a number four bytes");
    return number;
}

void ProtocolAssistant::sendNumber(uint16_t number) {
    checkShipping(skt.sendall(&number, sizeof(number), &wasClosed), "sending a number 2 bytes");
}

uint16_t ProtocolAssistant::receiveNumberTwoBytes() {
    uint16_t number;
    checkShipping(skt.recvall(&number, sizeof(number), &wasClosed), "receiving a number two bytes");
    return number;
}

void ProtocolAssistant::sendFloat(const float& fl) {
    checkShipping(skt.sendall(&fl, sizeof(fl), &wasClosed), "sending a float");
}

float ProtocolAssistant::receiveFloat() {
    float fl;
    checkShipping(skt.recvall(&fl, sizeof(fl), &wasClosed), "receiving a float");
    return fl;
}

void ProtocolAssistant::sendVector2D(const Vector2D& vector) {
    sendFloat(vector.x);
    sendFloat(vector.y);
}

Vector2D ProtocolAssistant::receiveVector2D() {
    auto x = receiveFloat();
    auto y = receiveFloat();
    Vector2D vec(x, y);
    return vec;
}

void ProtocolAssistant::sendBoolean(bool value) {
    uint8_t boolAsInt = (value ? 1 : 0);
    sendNumber(boolAsInt);
}

bool ProtocolAssistant::receiveBooelan() {
    auto booleanAsInt = receiveNumberOneByte();
    if (booleanAsInt != 0 && booleanAsInt != 1) {
        throw BrokenProtocol();
    }
    return (booleanAsInt == 1 ? true : false);
}
