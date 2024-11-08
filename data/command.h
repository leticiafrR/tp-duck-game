#ifndef COMMAND_DTA_H
#define COMMAND_DTA_H
#include "id.h"

enum class CommandCode : uint8_t {
    MoveRight_KeyUp,
    MoveRight_KeyDown,
    MoveLeft_KeyUp,
    MoveLeft_KeyDown,
    Jump,
    _quit
};

struct Command {
    CommandCode cmd;
    PlayerID_t playerId;
    explicit Command(CommandCode _cmd, PlayerID_t _playerId = 0): cmd(_cmd), playerId(_playerId) {}
    Command() = default;
};

#endif
