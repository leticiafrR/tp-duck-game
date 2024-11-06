#include "messageSender.h"

#include <utility>

/********************** IMPLEMENTATION OF MATCH START SETTING MSSG ******************************/
// cppcheck-suppress passedByValue
MatchStartSender::MatchStartSender(std::vector<PlayerData> playersData, Vector2D duckSize):
        matchStartDto(playersData, duckSize) {}

void MatchStartSender::execute(ServerProtocol& protocol) const {
    protocol.sendMatchStartSettings(matchStartDto);
}

/*********************** IMPLEMENTATION OF GAME START SETTINGS MSSG ***************************/
// cppcheck-suppress passedByValue
explicit GameSceneSender::GameSceneSender(GameSceneDto gameScene): gameScene(gameScene) {}

void GameSceneSender::execute(ServerProtocol& protocol) const {
    protocol.sendGameStartSettings(gameScene);
}

/*********************** IMPLEMENTATION OF GAME UPDATE MSSG ***************************/
// en el caso en que el gameWorld si me de una copia del snapdhoot original (que irà editando)
// cppcheck-suppress passedByValue
explicit GameUpdateSender::GameUpdateSender(Snapshot snapshot): snapshot(snapshot) {}

void GameUpdateSender::execute(ServerProtocol& protocol) const {
    protocol.sendGameUpdate(snapshot);
}

// /************************ IMPLEMENTATION OF GAMES RECOUNT MSSG *****************************/

// cppcheck-suppress passedByValue
GamesRecountSender::GamesRecountSender(std::unordered_map<PlayerID_t, int> results,
                                       bool matchEnded):
        gamesRecount(matchEnded, results) {}

void GamesRecountSender::execute(ServerProtocol& protocol) const {
    protocol.sendGamesRecount(gamesRecount);
}

/************************ IMPLEMENTATION OF MATCH RESULT MSSG *****************************/
explicit MatchExitSender::MatchExitSender(PlayerID_t finalWinner): finalWinner(finalWinner) {}

void MatchExitSender::execute(ServerProtocol& protocol) const {
    if (finalWinner != 0) {
        protocol.sendMatchWinner(finalWinner);
    }
    protocol.endConnection();
    return;
}
