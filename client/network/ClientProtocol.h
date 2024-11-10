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

#include "../../data/id.h"
#include "common/protocolAssistant.h"
#include "common/socket.h"

struct Snapshot;
struct MatchStartDto;
struct GameSceneDto;
struct GamesRecountDto;
struct Command;

struct BrokenProtocol: public std::runtime_error {
    BrokenProtocol():
            std::runtime_error("Error: client perceived that the server broke the protocol!") {}
};

class ClientProtocol {
private:
    Socket skt;
    ProtocolAssistant assistant;


    bool receiveResultJoining();

    MatchStartDto receiveMachStartDto();

    GameSceneDto receiveGameSceneDto();

    Snapshot receiveGameUpdateDto();

    bool receiveFinalGroupGame();

    GamesRecountDto receiveGamesRecountDto();

    PlayerID_t receiveMatchWinner();


public:
    explicit ClientProtocol(Socket&& skt);

    void sendNickname(const std::string& nickname);

    std::shared_ptr<NetworkMsg> receiveMessage();

    void sendCommand(CommandCode cmdCode);

    void endConnection();
};

#endif
