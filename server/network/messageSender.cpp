#include "messageSender.h"

#include <utility>

/********************** IMPLEMENTATION OF MATCH START SETTING MSSG ******************************/
MatchStartSender::MatchStartSender(const std::vector<PlayerData>& playersData, Vector2D duckSize):
        matchStartDto(playersData, duckSize) {}

void MatchStartSender::execute(ServerProtocol& protocol) const {
    protocol.sendMatchStartSettings(matchStartDto);
}

/*********************** IMPLEMENTATION OF GAME START SETTINGS MSSG ***************************/
GameSceneSender::GameSceneSender(const GameSceneDto& gameScene): gameScene(gameScene) {}

void GameSceneSender::execute(ServerProtocol& protocol) const {
    protocol.sendGameStartSettings(gameScene);
}

/*********************** IMPLEMENTATION OF GAME SNAPSHOT MSSG ***************************/
GameSnapshotSender::GameSnapshotSender(const Snapshot& snapshot): snapshot(snapshot) {}

void GameSnapshotSender::execute(ServerProtocol& protocol) const {
    protocol.sendGameUpdate(snapshot);
}

/*********************** IMPLEMENTATION OF GAME ENDING MSSG ***************************/
GameEndingSender::GameEndingSender(bool finalGroupGame): finalGroupGame(finalGroupGame) {}

void GameEndingSender::execute(ServerProtocol& protocol) const {
    protocol.sendGameEndingStatus(finalGroupGame);
}

/************************ IMPLEMENTATION OF GAMES RECOUNT MSSG *****************************/
GamesRecountSender::GamesRecountSender(const std::unordered_map<PlayerID_t, int>& results,
                                       bool matchEnded):
        gamesRecount(matchEnded, results) {}

void GamesRecountSender::execute(ServerProtocol& protocol) const {
    protocol.sendGamesRecount(gamesRecount);
}

/************************ IMPLEMENTATION OF MATCH RESULT MSSG *****************************/
MatchExitSender::MatchExitSender(PlayerID_t finalWinner): finalWinner(finalWinner) {}

void MatchExitSender::execute(ServerProtocol& protocol) const {
    if (finalWinner != 0) {
        protocol.sendMatchWinner(finalWinner);
    }
    protocol.endConnection();
    return;
}
