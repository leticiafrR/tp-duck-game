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
#include "data/id.h"
#include "data/networkMsg.h"
#include "data/snapshot.h"

struct Snapshot;
struct MatchStartDto;
struct GameSceneDto;
struct GamesRecountDto;
struct Command;
struct ActiveMatch;

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
    void sendMatchSelection(MatchID_t id);
    void sendStartMatchIntention();
    std::shared_ptr<NetworkMsg> receiveMessage();
    std::shared_ptr<AvailableMatches> receiveAvailableMatches();
    std::shared_ptr<ResultJoining> receiveResultJoining();
    PlayerID_t receiveMyID();

    void sendCommand(CommandCode cmdCode);
    void endConnection();
};

#endif
