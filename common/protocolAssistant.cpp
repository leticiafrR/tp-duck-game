#include "protocolAssistant.h"

ProtocolAssistant::ProtocolAssistant(Socket& skt): skt(skt) {}

void ProtocolAssistant::checkShipping(int cantBytes) {
    if (cantBytes == 0)
        throw ConnectionClosed();
}
void ProtocolAssistant::sendString(const std::string& cont) {
    uint16_t lenMessage = cont.size();
    lenMessage = htons(lenMessage);
    checkShipping(skt.sendall(&lenMessage, sizeof(uint16_t), &wasClosed));
    checkShipping(skt.sendall(cont.data(), cont.size(), &wasClosed));
}

std::string ProtocolAssistant::receiveString() {
    uint16_t lenMessage;
    checkShipping(skt.recvall(&lenMessage, sizeof(lenMessage), &wasClosed));
    lenMessage = ntohs(lenMessage);
    std::string buffer(lenMessage, '\0');
    checkShipping(skt.recvall(&buffer[0], lenMessage, &wasClosed));
    return buffer;
}

void ProtocolAssistant::sendNumber(uint8_t number) {
    checkShipping(skt.sendsome(&number, sizeof(number), &wasClosed));
}

uint8_t ProtocolAssistant::receiveNumberOneByte() {
    uint8_t number;
    checkShipping(skt.recvall(&number, sizeof(number), &wasClosed));
    return number;
}

void ProtocolAssistant::sendNumber(uint32_t number) {
    checkShipping(skt.sendsome(&number, sizeof(number), &wasClosed));
}

uint32_t ProtocolAssistant::receiveNumberFourBytes() {
    uint32_t number;
    checkShipping(skt.recvall(&number, sizeof(number), &wasClosed));
    return number;
}


void ProtocolAssistant::sendFloat(const float& fl) {
    checkShipping(skt.sendall(&fl, sizeof(fl), &wasClosed));
}

float ProtocolAssistant::receiveFloat() {
    float fl;
    skt.recvall(&fl, sizeof(fl), &wasClosed);
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
