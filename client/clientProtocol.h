#ifndef CLIENTPROTOCOL_H
#define CLIENTPROTOCOL_H

#include <string>

#include <stdint.h>

#include "../common/dataTransferObjects.h"
#include "../common/protocolAssistant.h"
#include "../common/socket.h"

class ClientProtocol {
private:
    Socket skt;
    ProtocolAssistant assistant;

public:
    explicit ClientProtocol(Socket&& skt);

    void sendNickName(const std::string& nickname);

    bool receiveStateOfJoining();

    MatchStartSettingsDto receiveMachStartSttings();

    GameStartSettingsDto receiveGameStartSettings();

    Snapshot receiveGameUpdate();

    GamesRecountDto receiveGamesRecount();

    PlayerID_t receiveMatchWinner();

    void endConnection();
};
#endif
