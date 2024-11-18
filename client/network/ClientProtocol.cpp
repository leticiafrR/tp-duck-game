#include "ClientProtocol.h"

#include <iostream>

#include "data/command.h"
#include "data/communicationCodes.h"
#include "data/dataTransferObjects.h"
#include "data/gameScene.h"
#include "data/snapshot.h"

struct BrokenProtocol: public std::runtime_error {
    BrokenProtocol():
            std::runtime_error("ERROR: client perceived that the server broke the protocol!") {}
};


ClientProtocol::ClientProtocol(Socket&& peer): skt(std::move(peer)), assistant(skt) {}

std::shared_ptr<NetworkMsg> ClientProtocol::receiveMessage() {
    auto typeMessage = assistant.receiveNumberOneByte();

    switch (typeMessage) {

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

        default:
            std::cout << "ERROR: the client recieved a unknown message  header! :"
                      << (int)typeMessage << "\n";
            throw BrokenProtocol();
    }
}

void ClientProtocol::sendNickname(const std::string& nickname) {
    assistant.sendNumber(NICKNAME);
    assistant.sendString(nickname);
}

void ClientProtocol::sendMatchSelection(MatchID_t id) {
    assistant.sendNumber(MATCH_SELECTION);
    assistant.sendNumber(id);
}

void ClientProtocol::sendStartMatchIntention() { assistant.sendNumber(START_MATCH_INTENTION); }


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

void ClientProtocol::sendCommand(CommandCode cmdCode) {
    assistant.sendNumber(COMMAND);
    assistant.sendNumber((uint8_t)cmdCode);
}

void ClientProtocol::endConnection() {
    skt.shutdown(2);
    skt.close();
}


std::shared_ptr<ResultJoining> ClientProtocol::receiveResultJoining() {
    if (assistant.receiveNumberOneByte() == RESULT_JOINING) {
        auto response = assistant.receiveNumberOneByte();
        if (response != 1 && response != 0)
            throw BrokenProtocol();
        return std::make_shared<ResultJoining>(ResultJoining(response));
    }
    throw BrokenProtocol();
}

std::shared_ptr<AvailableMatches> ClientProtocol::receiveAvailableMatches() {
    if (assistant.receiveNumberOneByte() == AVAILABLE_MATCHES) {
        auto numberMatches = assistant.receiveNumberOneByte();
        std::vector<DataMatch> matches;

        for (uint8_t i = 0; i < numberMatches; i++) {
            DataMatch match;
            match.currentPlayers = assistant.receiveNumberOneByte();
            match.maxPlayers = assistant.receiveNumberOneByte();
            match.matchID = assistant.receiveNumberFourBytes();
            match.creatorNickname = assistant.receiveString();
            matches.push_back(match);
        }
        return std::make_shared<AvailableMatches>(AvailableMatches(matches));
    }
    throw BrokenProtocol();
}

PlayerID_t ClientProtocol::receiveMyID() {
    if (assistant.receiveNumberOneByte() == IDENTIFICATION) {
        return assistant.receiveNumberFourBytes();
    }
    throw BrokenProtocol();
}
