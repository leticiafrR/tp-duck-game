#include "serverProtocol.h"

#include <utility>

ServerProtocol::ServerProtocol(Socket&& skt): skt(std::move(skt)), assistant(skt) {}

dataMatch ServerProtocol::ReceiveAMatch(bool& isConnected) {
    bool wasClosed = false;
    dataMatch newMatch;
    uint8_t typeMessage = assistant.reciveInt(wasClosed);
    if (typeMessage != NEW_GAME && typeMessage != JOIN_A_GAME) {
        return newMatch;  // o una excepcion
    }
    std::string name = assistant.reciveString(wasClosed);
    newMatch.clientName = name;
    if (typeMessage == NEW_GAME) {
        newMatch.ID = 0;

    } else if (typeMessage == JOIN_A_GAME) {
        uint8_t matchId = assistant.reciveInt(wasClosed);
        newMatch.ID = static_cast<size_t>(matchId);
    }

    if (wasClosed) {
        isConnected = false;
    }
    return newMatch;
}

dataMove ServerProtocol::ReceiveAMove(bool& isConnected) {

    bool wasClosed = false;
    dataMove newMove;
    uint8_t typeMessage = assistant.reciveInt(wasClosed);
    if (typeMessage != MOVEMENT) {
        // excepcion
    }
    std::string name = assistant.reciveString(wasClosed);
    newMove.playerName = name;
    uint8_t key = assistant.reciveInt(wasClosed);

    // No me convence el usar un booleano para manejar cuando se mantiene
    // o no presionada la tecla ya que deberia agregar otro atributo
    // que represente si la esta presionando o dejando de presionar
    // podria derivarse en la logica del servidor
    if (key == UP || key == LEFT || key == RIGHT || key == DOWN) {
        newMove.block = false;
        newMove.ID = key;

    } else if (key == KEY_UP || key == KEY_DOWN) {
        newMove.block = true;
        uint8_t moveID = assistant.reciveInt(wasClosed);
        newMove.ID = moveID;

    } else {
        // no es ninguna de las teclas
    }

    if (wasClosed) {
        isConnected = false;
    }
    return newMove;
}
