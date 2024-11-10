#include "messageSender.h"

#include <utility>

/********************** IMPLEMENTATION OF MATCH START SETTING MSSG ******************************/
MatchStartSender::MatchStartSender(const std::vector<PlayerData>& playersData, Vector2D duckSize):
        matchStartDto(playersData, duckSize) {}

std::string MatchStartSender::descriptionCont() const {
    return "The data of the start of the match\n";
}

void MatchStartSender::execute(ServerProtocol& protocol) const {
    protocol.sendMatchStartSettings(matchStartDto);
}

/*********************** IMPLEMENTATION OF GAME START SETTINGS MSSG ***************************/
GameSceneSender::GameSceneSender(const GameSceneDto& gameScene): gameScene(gameScene) {}

std::string GameSceneSender::descriptionCont() const {
    return "The data of the start of the game\n";
}
void GameSceneSender::execute(ServerProtocol& protocol) const {
    protocol.sendGameStartSettings(gameScene);
}

/*********************** IMPLEMENTATION OF GAME UPDATE MSSG ***************************/
// en el caso en que el gameWorld si me de una copia del snapdhoot original (que irà editando)
GameUpdateSender::GameUpdateSender(const Snapshot& snapshot): snapshot(snapshot) {}

std::string GameUpdateSender::descriptionCont() const { return "Snapshot!\n"; }

void GameUpdateSender::execute(ServerProtocol& protocol) const {
    protocol.sendGameUpdate(snapshot);
}

GameEndingSender::GameEndingSender(bool finalGroupGame): finalGroupGame(finalGroupGame) {}

std::string GameEndingSender::descriptionCont() const {
    return "Ending of the game (sending of its the last game of the group)\n";
}

void GameEndingSender::execute(ServerProtocol& protocol) const {
    protocol.sendGameEndingStatus(finalGroupGame);
}
// /************************ IMPLEMENTATION OF GAMES RECOUNT MSSG *****************************/

GamesRecountSender::GamesRecountSender(const std::unordered_map<PlayerID_t, int>& results,
                                       bool matchEnded):
        gamesRecount(matchEnded, results) {}
std::string GamesRecountSender::descriptionCont() const { return "Recount of the games won\n"; }
void GamesRecountSender::execute(ServerProtocol& protocol) const {
    protocol.sendGamesRecount(gamesRecount);
}

/************************ IMPLEMENTATION OF MATCH RESULT MSSG *****************************/
MatchExitSender::MatchExitSender(PlayerID_t finalWinner): finalWinner(finalWinner) {}
std::string MatchExitSender::descriptionCont() const {
    return "match exit-> sending the final winner of the match (or not) and also when proccesed "
           "will kill the client \n";
}

void MatchExitSender::execute(ServerProtocol& protocol) const {
    if (finalWinner != 0) {
        protocol.sendMatchWinner(finalWinner);
    }
    protocol.endConnection();
    return;
}
