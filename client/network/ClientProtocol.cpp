#include "ClientProtocol.h"

#include <iostream>

#include "data/command.h"
#include "data/communicationCodes.h"
#include "data/dataTransferObjects.h"
#include "data/gameScene.h"
#include "data/snapshot.h"

/*                  ---------PUBLIC METHODS---------                  */
ClientProtocol::ClientProtocol(Socket&& peer): skt(std::move(peer)), assistant(skt) {}

void ClientProtocol::sendNickname(const std::string& nickname) {
    assistant.sendNumber(NICKNAME);
    assistant.sendString(nickname);
}

uint16_t ClientProtocol::receiveLocalID() {
    if (assistant.receiveNumberOneByte() == IDENTIFICATION) {
        return assistant.receiveNumberTwoBytes();
    }
    throw BrokenProtocol();
}

std::shared_ptr<AvailableMatches> ClientProtocol::receiveAvailableMatches() {
    if (assistant.receiveNumberOneByte() == AVAILABLE_MATCHES) {
        auto numberMatches = assistant.receiveNumberOneByte();
        std::vector<DataMatch> matches(numberMatches);
        for (uint8_t i = 0; i < numberMatches; i++) {
            auto currentPlayers = assistant.receiveNumberOneByte();
            auto maxPlayers = assistant.receiveNumberOneByte();
            auto matchID = assistant.receiveNumberTwoBytes();
            auto creatorNickname = assistant.receiveString();
            matches[i] = DataMatch{currentPlayers, maxPlayers, matchID, creatorNickname};
        }
        return std::make_shared<AvailableMatches>(AvailableMatches(matches));
    }
    throw BrokenProtocol();
}

void ClientProtocol::sendMatchSelection(const MatchSelection& selection) {
    assistant.sendNumber(MATCH_SELECTION);
    assistant.sendNumber(selection.matchSelection);
    if (selection.matchSelection != 0) {
        assistant.sendNumber(selection.playersPerConection);
    }
}

std::shared_ptr<ResultJoining> ClientProtocol::receiveResultJoining() {
    if (assistant.receiveNumberOneByte() == RESULT_JOINING) {
        return std::make_shared<ResultJoining>(ResultJoining(assistant.receiveNumberOneByte()));
    }
    throw BrokenProtocol();
}

void ClientProtocol::sendStartMatchIntention() { assistant.sendNumber(START_MATCH_INTENTION); }

std::shared_ptr<ResultStartingMatch> ClientProtocol::receiveResultStarting() {
    if (assistant.receiveNumberOneByte() == RESULT_STARTING) {
        return std::make_shared<ResultStartingMatch>(assistant.receiveBooelan());
    }
    throw BrokenProtocol();
}

void ClientProtocol::sendCommand(const Command& cmd) {
    assistant.sendNumber(COMMAND);
    assistant.sendNumber((uint8_t)cmd.code);
    assistant.sendNumber((uint8_t)cmd.indexLocalPlayer);
}


std::shared_ptr<NetworkMsg> ClientProtocol::receiveMessage() {
    auto typeMessage = assistant.receiveNumberOneByte();

    switch (typeMessage) {

        case MATCH_STARTING_SETTINGS:
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

/*                  ---------PRIVATE METHODS---------                  */

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
    bool _gameOver = assistant.receiveBooelan();

    // receiving updates
    uint8_t numberUpdates = assistant.receiveNumberOneByte();
    std::unordered_map<PlayerID_t, PlayerEvent> _updates((size_t)numberUpdates);
    for (uint8_t i = 0; i < numberUpdates; i++) {
        // playerID
        auto ID = assistant.receiveNumberFourBytes();
        // PlayerEvent
        auto evMotion = assistant.receiveVector2D();
        auto evState = (DuckState)assistant.receiveNumberOneByte();
        auto evFlip = (Flip)assistant.receiveNumberOneByte();
        auto lookingUp = assistant.receiveBooelan();
        auto typeOnHand = (TypeCollectable)assistant.receiveNumberOneByte();
        auto isCrouched = assistant.receiveBooelan();
        auto cuacking = assistant.receiveBooelan();
        // building PlayerEvent
        _updates[ID] =
                PlayerEvent{evMotion, evState, evFlip, lookingUp, typeOnHand, isCrouched, cuacking};
    }
    // receiving raycastsEvents
    uint8_t numberProjectile = assistant.receiveNumberOneByte();
    std::vector<InstantProjectileEventDto> _raycastsEvents((size_t)numberProjectile);
    for (uint8_t i = 0; i < numberProjectile; i++) {
        auto type = (TypeProjectile)assistant.receiveNumberOneByte();
        auto origin = assistant.receiveVector2D();
        auto end = assistant.receiveVector2D();
        _raycastsEvents[i] = InstantProjectileEventDto{type, origin, end};
    }

    // receiving collectableDespawns
    uint8_t numberDespawns = assistant.receiveNumberOneByte();
    std::vector<CollectableID_t> _collectableDespawns((size_t)numberDespawns);
    for (uint8_t i = 0; i < numberDespawns; i++) {
        _collectableDespawns[i] = assistant.receiveNumberFourBytes();
    }

    // receiving collectableSpawns
    uint8_t numberSpawns = assistant.receiveNumberOneByte();
    std::cout << "[ClientProtocol]:Server has send us " << numberSpawns
              << "  number of spawn dtos\n";

    std::vector<CollectableSpawnEventDto> _collectableSpawns((size_t)numberSpawns);
    for (uint8_t i = 0; i < numberSpawns; i++) {
        CollectableID_t id = assistant.receiveNumberFourBytes();
        auto position = assistant.receiveVector2D();
        TypeCollectable type = (TypeCollectable)assistant.receiveNumberOneByte();
        _collectableSpawns[i] = CollectableSpawnEventDto{id, position, type};
    }

    return Snapshot(_gameOver, _updates, _raycastsEvents, _collectableDespawns, _collectableSpawns);
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


void ClientProtocol::endConnection() {
    skt.shutdown(2);
    skt.close();
}
