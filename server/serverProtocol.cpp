#include "serverProtocol.h"

ServerProtocol::ServerProtocol(Socket&& peer): skt(std::move(peer)), assistant(skt) {}

void ServerProtocol::sendResultOfJoining(bool success) {
    assistant.sendNumber(RESULT_JOINING);
    uint8_t response = success ? (uint8_t)1 : (uint8_t)0;
    assistant.sendNumber(response);
}

std::string ServerProtocol::receiveNickName() { return assistant.receiveString(); }

void ServerProtocol::sendMatchStartSettings(const MatchStartDto& matchStartDto) {
    assistant.sendNumber(MATCH_STARTING);

    // sending the quatity of players
    uint8_t numberPlayers = (uint8_t)matchStartDto.playersData.size();
    assistant.sendNumber(numberPlayers);
    // sending the data of each player
    for (uint8_t i = 0; i < numberPlayers; i++) {
        assistant.sendNumber(matchStartDto.playersData[i].playerID);
        assistant.sendString(matchStartDto.playersData[i].nickname);
        assistant.sendNumber((uint8_t)matchStartDto.playersData[i].playerSkin);
    }
    // sending a duck size (vector)
    assistant.sendVector2D(matchStartDto.duckSize);
    // probably latter this mssg will contain the size of other items
}

void ServerProtocol::sendGameStartSettings(const GameSceneDto& gameSceneDto) {
    assistant.sendNumber(GAME_SCENE);
    // sending the theme of the game
    assistant.sendString(gameSceneDto.theme);

    // sending the vector of transforms of platforms (except the ang)
    uint8_t numberPlatforms = (uint8_t)gameSceneDto.platforms.size();
    assistant.sendNumber(numberPlatforms);
    for (auto& platform: gameSceneDto.platforms) {
        assistant.sendVector2D(platform.GetSize());
        assistant.sendVector2D(platform.GetPos());
    }

    uint8_t numbGroundBlocks = (uint8_t)gameSceneDto.groundBlocks.size();
    assistant.sendNumber(numbGroundBlocks);
    for (auto& groundDto: gameSceneDto.groundBlocks) {
        auto numbEdges = groundDto.visibleEdges.size();
        // to indicate the visible edges we send two bytes: about the BTTM_TP and about the sides
        if (numbEdges == 4) {
            assistant.sendNumber(V_BTTM_TOP::BOTH);
            assistant.sendNumber(V_RG_LF::BOTH);
        } else if (numbEdges == 0) {
            assistant.sendNumber(V_BTTM_TOP::NONE);
            assistant.sendNumber(V_RG_LF::NONE);
        } else if (numbEdges == 3) {
            // at least has two sides
        }
    }
}

// its up to the server to set the id of the client
Command ServerProtocol::receiveCommand() {
    // deberìa recibir algun header?
    // uint8_t headerCommandType = assistant.receiveNumberOneByte();
    uint8_t commandID = assistant.receiveNumberOneByte();
    Command cmmd(commandID);
    return cmmd;
}

void ServerProtocol::sendGameUpdate(const Snapshot& update) {
    assistant.sendNumber(SNAPSHOT);

    uint8_t gameEnded = update.gameEnded ? (uint8_t)1 : (uint8_t)0;
    assistant.sendNumber(gameEnded);

    // sending the cont of the map player ID and position vector
    uint8_t numberElements = (uint8_t)update.ducksUpdate.size();
    assistant.sendNumber(numberElements);
    for (auto it = update.ducksUpdate.begin(); it != update.ducksUpdate.end(); ++it) {
        // playerID
        assistant.sendNumber(it->first);
        // duckupdate
        assistant.sendVector2D(it->second.position);
        assistant.sendNumber(it->second.status);
        assistant.sendNumber(it->second.flip);
    }
}

void ServerProtocol::sendGamesRecount(const GamesRecountDto& gamesRecount) {
    assistant.sendNumber(GAMES_RECOUNT);

    uint8_t matchEnded = gamesRecount.matchEnded ? (uint8_t)1 : (uint8_t)0;
    assistant.sendNumber(matchEnded);
    uint8_t numberElements = (uint8_t)gamesRecount.results.size();
    assistant.sendNumber(numberElements);
    for (auto it = gamesRecount.results.begin(); it != gamesRecount.results.end(); ++it) {
        assistant.sendNumber(it->first);
        assistant.sendNumber((uint8_t)it->second);
    }
}

void ServerProtocol::sendMatchWinner(PlayerID_t finalWinner) {
    assistant.sendNumber(END_MATCH);
    assistant.sendNumber(finalWinner);
}

void ServerProtocol::endConnection() {
    skt.shutdown(1);
    skt.close();
}
