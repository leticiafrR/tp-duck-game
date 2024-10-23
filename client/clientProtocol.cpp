#include "clientProtocol.h"

#include <utility>

ClientProtocol::ClientProtocol(Socket&& skt): skt(std::move(skt)), assistant(skt) {}

void ClientProtocol::SendNewGame(const std::string& name, bool& is_connected) {
    bool wasClosed = false;
    assistant.sendInt(NEW_GAME, wasClosed);
    if (wasClosed) {
        is_connected = false;
    }
}
void ClientProtocol::JoinGame(const std::string& name, bool& is_connected) {
    bool wasClosed = false;
    assistant.sendInt(JOIN_A_GAME, wasClosed);
    assistant.sendString(name, wasClosed);
    if (wasClosed) {
        is_connected = false;
    }
}
void ClientProtocol::SendMove(const std::string& name, const u_int8_t& move_id,
                              bool& is_connected) {
    bool wasClosed = false;
    assistant.sendInt(MOVEMENT, wasClosed);
    assistant.sendString(name, wasClosed);
    assistant.sendInt(move_id, wasClosed);
    if (wasClosed) {
        is_connected = false;
    }
}
void ClientProtocol::SendKeyHeld(const std::string& name, const bool& keyUp, const u_int8_t& moveID,
                                 bool& isConnected) {
    bool wasClosed = false;
    assistant.sendInt(MOVEMENT, wasClosed);
    assistant.sendString(name, wasClosed);
    if (keyUp) {
        assistant.sendInt(KEY_UP, wasClosed);
    } else {
        assistant.sendInt(KEY_DOWN, wasClosed);
    }

    assistant.sendInt(moveID, wasClosed);

    if (wasClosed) {
        isConnected = false;
    }
}

void ClientProtocol::SendName(const std::string& playerName, bool& isConnected) {
    bool wasClosed = false;
    assistant.sendInt(NAME, wasClosed);
    assistant.sendString(playerName, wasClosed);
    if (wasClosed) {
        isConnected = false;
    }
}
dataMatch ClientProtocol::ReceiveMatch(bool& isConnected) {
    dataMatch match;
    bool wasClosed = false;
    uint8_t type = assistant.reciveInt(wasClosed);
    if (type != A_MATCH) {
        // lanzo excepcion
    }

    uint8_t newMatchID = assistant.reciveInt(wasClosed);
    match.ID = newMatchID;
    uint8_t newQuantityPlayers = assistant.reciveInt(wasClosed);
    match.quantityPlayers = newQuantityPlayers;
    uint8_t newMAXPlayers = assistant.reciveInt(wasClosed);
    match.MAXPlayers = newMAXPlayers;

    if (wasClosed) {
        isConnected = false;
    }
    return match;
}
