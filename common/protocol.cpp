#include "protocol.h"

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include <arpa/inet.h>

#include "socket.h"


Protocol::Protocol(Socket&& skt): skt(std::move(skt)) {}

uint8_t Protocol::reciveInt(bool& wasClosed) {
    uint8_t int;

    skt.recvall(&int, sizeof(int), &wasClosed);

    return int;
}

std::string Protocol::reciveString(bool& wasClosed) {
    uint16_t size;
    skt.recvall(&size, sizeof(size), &wasClosed);

    uint16_t sizeHost = ntohs(size);
    std::vector<char> stringBuffer(sizeHost + 1);

    skt.recvall(stringBuffer.data(), sizeHost, &wasClosed);

    stringBuffer[sizeHost] = '\0';
    std::string string(stringBuffer.data());
    return string;
}

void Protocol::sendInt(const uint8_t& int, bool& wasClosed) {
    skt.sendall(&int, sizeof(int), &wasClosed);
}

void Protocol::sendString(const std::string& string, bool& wasClosed) {
    uint16_t size = htons(string.size());
    skt.sendall(reinterpret_cast<const char*>(&size), sizeof(size), &wasClosed);
    skt.sendall(string.c_str(), string.size(), &wasClosed);
}
