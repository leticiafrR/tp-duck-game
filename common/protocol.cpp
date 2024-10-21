#include "protocol.h"

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include <arpa/inet.h>
#include "socket.h"


Protocol::Protocol(Socket&& skt): skt(std::move(skt)) {}

u_int8_t Protocol::recive_a_int(bool& was_closed) {
    u_int8_t int;

    skt.recvall(&int, sizeof(int), &was_closed);

    return int;
}

std::string Protocol::recive_a_string(bool& was_closed) {
    u_int16_t size;
    skt.recvall(&size, sizeof(size), &was_closed);

    u_int16_t size_host = ntohs(size);
    std::vector<char> stringBuffer(size_host + 1);

    skt.recvall(stringBuffer.data(), size_host, &was_closed);

    stringBuffer[size_host] = '\0';
    std::string string(stringBuffer.data());
    return string;
}

void Protocol::send_a_int(const u_int8_t& int, bool& was_closed) {
    skt.sendall(&int, sizeof(int), &was_closed);

}

void Protocol::send_a_string(const std::string& string, bool& was_closed) {
    uint16_t size = htons(string.size());
    skt.sendall(reinterpret_cast<const char*>(&size), sizeof(size), &was_closed);

    skt.sendall(string.c_str(), string.size(), &was_closed);

}
