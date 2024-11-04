#include "serverProtocol.h"

ServerProtocol::ServerProtocol(Socket&& peer): skt(std::move(peer)), assistant(skt) {}

void ServerProtocol::sendResultOfJoining(const bool& success) {
    uint8_t response = success ? (uint8_t)1 : (uint8_t)0;
    assistant.sendNumber(response);
}

std::string ServerProtocol::receiveNickName() { return assistant.receiveString(); }

void ServerProtocol::sendMatchStartSettings(MatchStartSettingsDto matchStartSettings) {
    // sending the quatity of players
    uint8_t numberPlayers = (uint8_t)matchStartSettings.playerIDs.size();
    assistant.sendNumber(numberPlayers);
    // sending the data of each player
    for (uint8_t i = 0; i < numberPlayers; i++) {
        // ID
        assistant.sendNumber(matchStartSettings.playerIDs[i]);
        // Nickname
        assistant.sendString(matchStartSettings.playerNicknames[i]);
        // number skin
        assistant.sendNumber((uint8_t)matchStartSettings.playerSkins[i]);
    }
    // sending a duck size (vector)
    assistant.sendFloat(matchStartSettings.duckSize.x);
    assistant.sendFloat(matchStartSettings.duckSize.y);
}

void ServerProtocol::sendGameStartSettings(GameStartSettingsDto gameStartSettings) {
    // sending the theme of the game
    assistant.sendString(gameStartSettings.theme);
    // sending the vector of size y luego posicion
    uint8_t numberPlatforms = (uint8_t)gameStartSettings.platforms.size();
    assistant.sendNumber(numberPlatforms);
    for (uint8_t i = 0; i < numberPlatforms; i++) {
        assistant.sendVector2D(gameStartSettings.platforms[i].GetSize());
        assistant.sendVector2D(gameStartSettings.platforms[i].GetPos());
    }
}
// its up to the server to set the id of the client
Command ServerProtocol::receiveCommand() {
    uint8_t headerCommandType = assistant.receiveNumberOneByte();
    uint8_t commandID = assistant.receiveNumberOneByte();
    Command cmmd(std::move(headerCommandType), std::move(commandID));
    return cmmd;
}

void ServerProtocol::sendGameUpdate(Snapshot update) {
    uint8_t gameEnded = update.gameEnded ? (uint8_t)1 : (uint8_t)0;
    assistant.sendNumber(gameEnded);
    // sending the cont of the map player ID and position vector
    uint8_t numberElements = (uint8_t)update.positionsUpdate.size();
    assistant.sendNumber(numberElements);
    for (auto it = update.positionsUpdate.begin(); it != update.positionsUpdate.end(); ++it) {
        assistant.sendNumber(it->first);
        assistant.sendVector2D(it->second);
    }
}

void ServerProtocol::sendGamesRecount(GamesRecountDto gamesRecount) {
    uint8_t matchEnded = gamesRecount.matchEnded ? (uint8_t)1 : (uint8_t)0;
    assistant.sendNumber(matchEnded);
    uint8_t numberElements = (uint8_t)gamesRecount.results.size();
    assistant.sendNumber(numberElements);
    for (auto it = gamesRecount.results.begin(); it != gamesRecount.results.end(); ++it) {
        assistant.sendNumber(it->first);
        assistant.sendNumber((uint8_t)it->second);
    }
}

void ServerProtocol::sendMatchWinner(PlayerID_t finalWinner) { assistant.sendNumber(finalWinner); }

void ServerProtocol::endConnection() {
    skt.shutdown(1);
    skt.close();
}
