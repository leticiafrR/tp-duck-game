#ifndef PLAYER_IDENTIFIER
#define PLAYER_IDENTIFIER
#include "data/id.h"

class PlayerIdentifier {
public:
    static PlayerID_t GeneratePlayerID(uint16_t connectionID, uint8_t iPlayer) {
        return (static_cast<PlayerID_t>(connectionID) << 8) | static_cast<uint32_t>(iPlayer);
    }

    static void DecomposePlayerID(uint32_t playerId, uint16_t& connectionID, uint8_t& iPlayer) {
        connectionID = (playerId >> 8) & 0xFFFF;
        iPlayer = playerId & 0xFF;
    }
};

#endif
