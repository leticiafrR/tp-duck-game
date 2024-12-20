#ifndef CLIENTPROTOCOL_H
#define CLIENTPROTOCOL_H

#include <algorithm>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <stdint.h>

#include "common/protocolAssistant.h"
#include "common/socket.h"
#include "data/command.h"
#include "data/dataTransferObjects.h"
#include "data/gameScene.h"
#include "data/id.h"
#include "data/matchSelection.h"
#include "data/networkMsg.h"
#include "data/snapshot.h"

class ClientProtocol {
private:
    Socket skt;
    ProtocolAssistant assistant;

    MatchStartDto receiveMachStartDto();
    GameSceneDto receiveGameSceneDto();
    Snapshot receiveGameUpdateDto();
    bool receiveFinalGroupGame();
    GamesRecountDto receiveGamesRecountDto();
    PlayerID_t receiveMatchWinner();

public:
    explicit ClientProtocol(Socket&& skt);
    void sendNickname(const std::string& nickname);
    uint16_t receiveLocalID();

    std::shared_ptr<AvailableMatches> receiveAvailableMatches();
    void sendMatchSelection(const MatchSelection& selection);
    std::shared_ptr<ResultJoining> receiveResultJoining();

    void sendStartMatchIntention();
    std::shared_ptr<ResultStartingMatch> receiveResultStarting();

    std::shared_ptr<NetworkMsg> receiveMessage();
    void sendCommand(const Command& cmd);

    void endConnection();

    // not copyable
    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;
};

#endif
