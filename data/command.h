#ifndef COMMAND_DTA_H
#define COMMAND_DTA_H
#include "id.h"

enum class CommandCode : uint8_t {
    MoveRight_KeyUp,
    MoveRight_KeyDown,

    MoveLeft_KeyUp,
    MoveLeft_KeyDown,

    Jump,
    _quit,

    UseItem_KeyDown,
    UseItem_KeyUp,

    LookUp_KeyDown,
    LookUp_KeyUp,

    Crouch_KeyDown,  // empezar a agacharse
    Crouch_KeyUp

};
// OJO FALTA QUE LOS PROTOCOLOS ENVIEN AHORA UN COMMAND ASÌ
struct Command {
    CommandCode code;
    uint8_t indexLocalPlayer;  // 0 hasta  n-1
    // will  be seted by the server
    PlayerID_t playerID;
    explicit Command(CommandCode _code, uint8_t _indexLocalPlayer, PlayerID_t _playerID = 0):
            code(_code), indexLocalPlayer(_indexLocalPlayer), playerID(_playerID) {}
    Command() = default;
};

#endif
