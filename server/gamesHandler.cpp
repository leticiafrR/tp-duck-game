#include "gamesHandler.h"

#include <random>
#include <utility>

#include "common/timeManager.h"
#include "network/messageSender.h"


#define MAX_CMMDS_PER_TICK 10
#define TPS 20
#define PLAYERS_TO_WIN_BY_DEFAULT 1

GamesHandler::GamesHandler(Config& config, SafeMap<PlayerID_t, PlayerInfo>& players,
                           std::shared_ptr<Queue<Command>> commandQueue,
                           std::atomic<MATCH_STATUS>& matchStatus):
        availableLevels(config.getAvailableLevels()),
        players(players),
        commandQueue(commandQueue),
        matchStatus(matchStatus) {
    auto playerIDs = players.getKeys();
    for (auto& id: playerIDs) {
        playerPointsRecord[id] = 0;
    }
}

PlayerID_t GamesHandler::whoWon() { return matchWinner; }

void GamesHandler::playGroupOfGames() {
    for (int i = 0; i < GAMES_IN_GROUP && matchStatus == MATCH_ON_COURSE; i++) {
        playOneGame();
        broadcastGameMssg(std::make_shared<GameEndingSender>(i == (GAMES_IN_GROUP - 1) ||
                                                             matchStatus != MATCH_ON_COURSE));
    }
    updateMatchWinnerStatus();
    broadcastGameMssg(std::make_shared<GamesRecountSender>(playerPointsRecord,
                                                           matchStatus != MATCH_ON_COURSE));
}

void GamesHandler::updateMatchWinnerStatus() {

    if (matchStatus == WON_BY_DEFAULT) {
        matchWinner = currentGame->WhoWon();
        return;
    }
    if (currentRecord >= GAMES_TO_WIN_MATCH) {
        bool existsMatchWinner = false;

        for (auto it = playerPointsRecord.begin(); it != playerPointsRecord.end(); ++it) {
            if (!existsMatchWinner && it->second == currentRecord) {
                existsMatchWinner = true;
                matchWinner = it->first;
            } else if (existsMatchWinner && it->second == currentRecord) {
                existsMatchWinner = false;
                matchWinner = 0;
                break;
            }
        }
        if (existsMatchWinner) {
            matchStatus = NATURALLY_WON;
        }
    }
}

void GamesHandler::playOneGame() {
    clearQueue();
    auto playerIDs = players.getKeys();
    checkNumberPlayers();
    // can take out the first argument
    currentGame.emplace(Vector2D(INFINITY, INFINITY), playerIDs, getRandomLevel());
    broadcastGameMssg(std::make_shared<GameSceneSender>(std::move(currentGame->getSceneDto())));
    gameLoop();
    registerGameWinnerPoint();
}


void GamesHandler::registerGameWinnerPoint() {
    checkNumberPlayers();
    PlayerID_t gameWinner = currentGame->WhoWon();
    if (playerPointsRecord.find(gameWinner) != playerPointsRecord.end()) {
        int playerRecord = playerPointsRecord[gameWinner] += 1;
        if (playerRecord > currentRecord) {
            currentRecord = playerRecord;
        }
    }

    if (players.size() == PLAYERS_TO_WIN_BY_DEFAULT)
        matchStatus = WON_BY_DEFAULT;
}

void GamesHandler::gameLoop() {

    TimeManager timeManager(TPS);

    while (!currentGame->IsOver() && players.size() > NOT_ENOUGH_NUMBER_PLAYERS) {
        Command cmmd;
        for (int i = 0; i < MAX_CMMDS_PER_TICK && commandQueue->try_pop(std::ref(cmmd)); i++) {
            if (cmmd.cmd == CommandCode::_quit)
                // currentGame->quitPlayer(cmmd.playerId);
                continue;
            else
                currentGame->HandleCommand(cmmd);
        }
        auto deltaTime = timeManager.updateTickTimer();
        currentGame->Update(deltaTime);
        broadcastGameMssg(std::make_shared<GameUpdateSender>(currentGame->GetSnapshot()));
        timeManager.sleepIfNeeded();
    }
}

void GamesHandler::broadcastGameMssg(const std::shared_ptr<MessageSender>& message) {
    checkNumberPlayers();
    players.applyToValues(
            [&message](PlayerInfo& player) { player.senderQueue->try_push(message); });
    checkNumberPlayers();
}

void GamesHandler::checkNumberPlayers() {
    if (players.size() == 0) {
        throw RunOutOfPlayers();
    }
}

std::string GamesHandler::getRandomLevel() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, availableLevels.size() - 1);
    return availableLevels[dist(gen)];
}

void GamesHandler::clearQueue() {
    Command cmmd;
    while (commandQueue->try_pop(std::ref(cmmd))) {}
}
