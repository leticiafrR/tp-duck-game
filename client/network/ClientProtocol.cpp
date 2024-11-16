#include "ClientProtocol.h"

#include <iostream>

#include "data/command.h"
#include "data/communicationCodes.h"
#include "data/dataTransferObjects.h"
#include "data/gameScene.h"
#include "data/snapshot.h"


ClientProtocol::ClientProtocol(Socket&& peer): skt(std::move(peer)), assistant(skt) {}

void ClientProtocol::sendNickname(const std::string& nickname) {
    assistant.sendNumber(NICKNAME);
    assistant.sendString(nickname);
}


std::shared_ptr<NetworkMsg> ClientProtocol::receiveMessage() {
    auto typeMessage = assistant.receiveNumberOneByte();

    switch (typeMessage) {

        case RESULT_JOINING:
            return std::make_shared<ResultJoining>(receiveResultJoining());

        case MATCH_STARTING:
            return std::make_shared<MatchStartDto>(receiveMachStartDto());

        case GAME_SCENE:
            return std::make_shared<GameSceneDto>(receiveGameSceneDto());

        case SNAPSHOT:
            return std::make_shared<Snapshot>(receiveGameUpdateDto());

        case GAME_ENDING:
            return std::make_shared<FinalGroupGame>(receiveFinalGroupGame());

        case GAMES_RECOUNT:
            return std::make_shared<GamesRecountDto>(receiveGamesRecountDto());

        case END_MATCH:
            return std::make_shared<FinalWinner>(receiveMatchWinner());

        case ACTIVE_MATCHES:
            return std::make_shared<ListActiveMatches>(receiveActiveMatches());

        default:
            std::cout << "ERR: the client recieved a unknown message  header!\n";
            throw BrokenProtocol();
    }
}

bool ClientProtocol::receiveResultJoining() {
    auto response = assistant.receiveNumberOneByte();
    if (response != 1 && response != 0)
        throw BrokenProtocol();
    return response;
}

MatchStartDto ClientProtocol::receiveMachStartDto() {
    auto numberPlayers = assistant.receiveNumberOneByte();
    std::vector<PlayerData> playersData((size_t)numberPlayers);
    for (uint8_t i = 0; i < numberPlayers; i++) {
        auto ID = assistant.receiveNumberFourBytes();
        auto nickname = assistant.receiveString();
        auto numberSkin = assistant.receiveNumberOneByte();
        playersData[i] = PlayerData{ID, numberSkin, std::move(nickname)};
    }
    Vector2D duckSize = assistant.receiveVector2D();

    return MatchStartDto{std::move(playersData), std::move(duckSize)};
}

GameSceneDto ClientProtocol::receiveGameSceneDto() {
    auto theme = assistant.receiveString();

    auto numberPlatforms = assistant.receiveNumberOneByte();
    std::vector<Transform> platforms(numberPlatforms);
    for (uint8_t i = 0; i < numberPlatforms; i++) {
        Vector2D size = assistant.receiveVector2D();
        Vector2D pos = assistant.receiveVector2D();
        platforms[i] = Transform(pos, size);
    }

    auto numberGroundB = assistant.receiveNumberOneByte();
    std::vector<GroundDto> groundBlocks(numberGroundB);
    for (uint8_t i = 0; i < numberGroundB; i++) {
        // receiving the visible edges
        std::set<VISIBLE_EDGES> edges;
        auto bttm_tp = assistant.receiveNumberOneByte();
        if (bttm_tp == V_BTTM_TOP::BOTH_TB || bttm_tp == V_BTTM_TOP::TP)
            edges.insert(VISIBLE_EDGES::TOP);

        if (bttm_tp == V_BTTM_TOP::BOTH_TB || bttm_tp == V_BTTM_TOP::BTTM)
            edges.insert(VISIBLE_EDGES::BOTTOM);

        auto rg_lf = assistant.receiveNumberOneByte();
        if (rg_lf == V_RG_LF::BOTH_RL || rg_lf == V_RG_LF::RG)
            edges.insert(VISIBLE_EDGES::RIGHT);

        if (rg_lf == V_RG_LF::BOTH_RL || rg_lf == V_RG_LF::LF)
            edges.insert(VISIBLE_EDGES::LEFT);

        // receiving the data of their transforms
        auto size = assistant.receiveVector2D();
        auto pos = assistant.receiveVector2D();
        Transform transform(pos, size);

        // building the GroundDto
        groundBlocks[i] = GroundDto{std::move(transform), std::move(edges)};
    }
    return GameSceneDto{theme, platforms, groundBlocks};
}

Snapshot ClientProtocol::receiveGameUpdateDto() {
    auto gameOverCode = assistant.receiveNumberOneByte();
    if (gameOverCode != 1 && gameOverCode != 0)
        throw BrokenProtocol();
    bool gameOver = gameOverCode == 1 ? true : false;

    // receiving the cont of the map player ID and position vector
    std::unordered_map<PlayerID_t, PlayerEvent> updates;
    uint8_t numberUpdates = assistant.receiveNumberOneByte();
    for (uint8_t i = 0; i < numberUpdates; i++) {
        // playerID
        auto ID = assistant.receiveNumberFourBytes();
        // PlayerEvent
        auto evMotion = assistant.receiveVector2D();
        auto evState = (DuckState)assistant.receiveNumberOneByte();
        auto evFlip = (Flip)assistant.receiveNumberOneByte();
        // building PlayerEvent
        updates[ID] = PlayerEvent{evMotion, evState, evFlip};
    }
    std::vector<InstantProjectileEventDto> projectiles;
    uint8_t numberProjectile = assistant.receiveNumberOneByte();
    for (uint8_t i = 0; i < numberProjectile; i++) {

        // auto speed = assistant.receiveFloat();
        auto type = (TypeProjectile)assistant.receiveNumberOneByte();
        auto origin = assistant.receiveVector2D();
        auto end = assistant.receiveVector2D();
        projectiles.emplace_back(InstantProjectileEventDto(type, origin, end));
    }

    return Snapshot(gameOver, updates, projectiles);
}

bool ClientProtocol::receiveFinalGroupGame() {
    auto finalGroupGame = assistant.receiveNumberOneByte();
    if (finalGroupGame != 1 && finalGroupGame != 0)
        throw BrokenProtocol();
    return finalGroupGame;
}

GamesRecountDto ClientProtocol::receiveGamesRecountDto() {

    auto matchEndedCode = assistant.receiveNumberOneByte();
    if (matchEndedCode != 1 && matchEndedCode != 0)
        throw BrokenProtocol();
    bool matchEnded = matchEndedCode;

    // receiving the map of games won by each player
    std::unordered_map<PlayerID_t, int> results;
    auto numberElements = assistant.receiveNumberOneByte();
    for (uint8_t i = 0; i < numberElements; i++) {
        auto id = assistant.receiveNumberFourBytes();
        auto count = assistant.receiveNumberOneByte();
        results[id] = (int)count;
    }
    return GamesRecountDto(matchEnded, std::move(results));
}

PlayerID_t ClientProtocol::receiveMatchWinner() { return assistant.receiveNumberFourBytes(); }

void ClientProtocol::sendRequestJoinMatch(const PlayerID_t& matchID) {
    assistant.sendNumber(LOG_MATCH);
    assistant.sendNumber(matchID);
}

void ClientProtocol::sendCommand(CommandCode cmdCode) {
    assistant.sendNumber(COMMAND);
    assistant.sendNumber((uint8_t)cmdCode);
}

void ClientProtocol::endConnection() {
    skt.shutdown(2);
    skt.close();
}

ListActiveMatches ClientProtocol::receiveActiveMatches() {
    auto numberMatches = assistant.receiveNumberOneByte();
    std::unordered_map<PlayerID_t, ActiveMatch> matches;
    for (uint8_t i = 0; i < numberMatches; i++) {
        ActiveMatch match;
        auto id = assistant.receiveNumberFourBytes();
        match.name = assistant.receiveString();
        match.actualPlayers = assistant.receiveNumberOneByte();
        match.maxPlayers = assistant.receiveNumberOneByte();
        matches[id] = match;
    }
    return ListActiveMatches(matches);
}
