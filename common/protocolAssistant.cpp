#include "protocolAssistant.h"

ProtocolAssistant::ProtocolAssistant(Socket& skt): skt(skt) {}

void ProtocolAssistant::checkShipping(int cantBytes) {
    if (cantBytes == 0)
        throw ConnectionFailed();
}
void ProtocolAssistant::sendString(const std::string& cont) {
    uint16_t lenMessage = cont.size();
    lenMessage = htons(lenMessage);
    try {
        checkShipping(skt.sendall(&lenMessage, sizeof(uint16_t), &wasClosed));
        checkShipping(skt.sendall(cont.data(), cont.size(), &wasClosed));
    } catch (const LibError& e) {
        throw ConnectionFailed();
    }
}

std::string ProtocolAssistant::receiveString() {
    uint16_t lenMessage;
    try {
        checkShipping(skt.recvall(&lenMessage, sizeof(lenMessage), &wasClosed));
        lenMessage = ntohs(lenMessage);
        std::string buffer(lenMessage, '\0');
        checkShipping(skt.recvall(&buffer[0], lenMessage, &wasClosed));
        return buffer;
    } catch (const LibError& e) {
        throw ConnectionFailed();
    }
}

void ProtocolAssistant::sendNumber(uint8_t number) {
    try {
        checkShipping(skt.sendsome(&number, sizeof(number), &wasClosed));
    } catch (const LibError& e) {
        throw ConnectionFailed();
    }
}

uint8_t ProtocolAssistant::receiveNumberOneByte() {
    uint8_t number;
    try {
        checkShipping(skt.recvall(&number, sizeof(number), &wasClosed));
    } catch (const LibError& e) {
        throw ConnectionFailed();
    }
    return number;
}

void ProtocolAssistant::sendNumber(uint32_t number) {
    try {
        checkShipping(skt.sendsome(&number, sizeof(number), &wasClosed));
    } catch (const LibError& e) {
        throw ConnectionFailed();
    }
}

uint32_t ProtocolAssistant::receiveNumberFourBytes() {
    uint32_t number;
    try {
        checkShipping(skt.recvall(&number, sizeof(number), &wasClosed));
    } catch (const LibError& e) {
        throw ConnectionFailed();
    }
    return number;
}


void ProtocolAssistant::sendFloat(const float& fl) {
    try {
        checkShipping(skt.sendall(&fl, sizeof(fl), &wasClosed));
    } catch (const LibError& e) {
        throw ConnectionFailed();
    }
}

float ProtocolAssistant::receiveFloat() {
    float fl;
    try {
        checkShipping(skt.recvall(&fl, sizeof(fl), &wasClosed));
    } catch (const LibError& e) {
        throw ConnectionFailed();
    }
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
