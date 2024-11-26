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

    Crouch_KeyDown,
    Crouch_KeyUp,

    Cuack,

    CollectItem,
    DropItem
};

struct Command {
    CommandCode code;
    uint8_t indexLocalPlayer;
    PlayerID_t playerId;
    explicit Command(CommandCode _code, uint8_t _indexLocalPlayer, PlayerID_t _playerID = 0):
            code(_code), indexLocalPlayer(_indexLocalPlayer), playerId(_playerID) {}
    Command() = default;
};

#endif
