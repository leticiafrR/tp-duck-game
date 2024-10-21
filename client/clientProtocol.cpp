#include "clientProtocol.h"

#include <utility>

ClientProtocol::ClientProtocol(Socket&& skt): skt(std::move(skt)), assistant(skt) {}

void ClientProtocol::SendNewGame(const std::string& name, bool& is_connected) {
    bool was_closed = false;
    assistant.sendInt(NEW_GAME, was_closed);
    if (was_closed) {
        is_connected = false;
    }
}
void ClientProtocol::JoinGame(const std::string& name, bool& is_connected) {
    bool was_closed = false;
    assistant.sendInt(JOIN_A_GAME, was_closed);
    assistant.sendString(name, was_closed);
    if (was_closed) {
        is_connected = false;
    }
}
void ClientProtocol::SendMove(const std::string& name, const u_int8_t& move_id,
                              bool& is_connected) {
    bool was_closed = false;
    assistant.sendInt(MOVEMENT, was_closed);
    assistant.sendString(name, was_closed);
    assistant.sendInt(move_id, was_closed);
    if (was_closed) {
        is_connected = false;
    }
}
void ClientProtocol::SendKeyHeld(const std::string& name, const bool& key_on,
                                 const u_int8_t& move_id, bool& is_connected) {
    bool was_closed = false;
    assistant.sendInt(MOVEMENT, was_closed);
    assistant.sendString(name, was_closed);
    if (key_on) {
        assistant.sendInt(KEY_ON, was_closed);
    } else {
        assistant.sendInt(KEY_OFF, was_closed);
    }

    assistant.sendInt(move_id, was_closed);

    if (was_closed) {
        is_connected = false;
    }
}
