#include "protocolAssistant.h"

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include <arpa/inet.h>

#include "socket.h"


ProtocolAssistant::ProtocolAssistant(Socket& skt): skt(skt) {}

uint8_t ProtocolAssistant::reciveInt(bool& wasClosed) {
    uint8_t num;

    skt.recvall(&num, sizeof(int), &wasClosed);

    return num;
}

std::string ProtocolAssistant::reciveString(bool& wasClosed) {
    uint16_t size;
    skt.recvall(&size, sizeof(size), &wasClosed);

    uint16_t sizeHost = ntohs(size);
    std::vector<char> stringBuffer(sizeHost + 1);

    skt.recvall(stringBuffer.data(), sizeHost, &wasClosed);

    stringBuffer[sizeHost] = '\0';
    std::string string(stringBuffer.data());
    return string;
}

void ProtocolAssistant::sendInt(const uint8_t& num, bool& wasClosed) {
    skt.sendall(&num, sizeof(int), &wasClosed);
}

void ProtocolAssistant::sendString(const std::string& string, bool& wasClosed) {
    uint16_t size = htons(string.size());
    skt.sendall(reinterpret_cast<const char*>(&size), sizeof(size), &wasClosed);
    skt.sendall(string.c_str(), string.size(), &wasClosed);
}

void ProtocolAssistant::SendFloat(const float& ang, bool& wasClosed) {

    skt.sendall(&ang, sizeof(float), &wasClosed);
}

float ProtocolAssistant::ReceiveFloat(bool& wasClosed) {
    float ang;
    skt.recvall(&ang, sizeof(ang), &wasClosed);
    return ang;
}

void ProtocolAssistant::SendSizeT(const size_t& ang, bool& wasClosed) {

    skt.sendall(&ang, sizeof(float), &wasClosed);
}

size_t ProtocolAssistant::ReceiveSizeT(bool& wasClosed) {
    size_t ang;
    skt.recvall(&ang, sizeof(ang), &wasClosed);
    return ang;
}
