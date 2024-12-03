#include "gamesHandler.h"

#include <random>
#include <utility>

#include "common/playerIdentifier.h"
#include "common/timeManager.h"
#include "network/messageSender.h"


#define MAX_CMMDS_PER_TICK 10
#define TPS 20
#define PLAYERS_TO_WIN_BY_DEFAULT 1

GamesHandler::GamesHandler(const Config& config,
                           SafeMap<uint16_t, Queue<std::shared_ptr<MessageSender>>*>& clientsQueues,
                           SafeMap<uint16_t, ClientInfo>& playersPerClient,
                           std::shared_ptr<Queue<Command>> matchQueue,
                           std::atomic<MATCH_STATUS>& matchStatus,
                           std::atomic<uint8_t>& currentPlayers):
        clientsQueues(clientsQueues),
        playersPerClient(playersPerClient),
        matchQueue(matchQueue),
        matchStatus(matchStatus),
        currentPlayers(currentPlayers),
        config(config) {

    playersPerClient.applyToItems([&playerPointsRecord = this->playerPointsRecord](
                                          uint16_t baseID, const ClientInfo& infoConnection) {
        for (uint8_t i = 0; i < infoConnection.playersPerConnection; i++) {
            PlayerID_t playerID = PlayerIdentifier::GeneratePlayerID(baseID, i);
            playerPointsRecord[playerID] = 0;
        }
    });
}

PlayerID_t GamesHandler::whoWon() { return matchWinner; }

void GamesHandler::playGroupOfGames() {
    for (int i = 0; i < config.gamesInGroup() && matchStatus == MATCH_ON_COURSE; i++) {
        playOneGame();
        broadcastGameMssg(std::make_shared<GameEndingSender>(i == (config.gamesInGroup() - 1) ||
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
    if (currentRecord >= config.gamesToWinMatch()) {
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

    std::vector<PlayerID_t> playersIDs;

    playersPerClient.applyToItems([&playersIDs](uint16_t baseID, const ClientInfo& infoConnection) {
        for (uint8_t i = 0; i < infoConnection.playersPerConnection; i++) {
            PlayerID_t playerID = PlayerIdentifier::GeneratePlayerID(baseID, i);
            playersIDs.push_back(playerID);
        }
    });
    checkNumberPlayers();
    currentGame.emplace(playersIDs, getRandomLevel(), config);
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

    if (currentPlayers == PLAYERS_TO_WIN_BY_DEFAULT)
        matchStatus = WON_BY_DEFAULT;
}

void GamesHandler::gameLoop() {

    TimeManager timeManager(TPS);

    while (!currentGame->IsOver()) {
        Command cmmd;
        for (int i = 0; i < MAX_CMMDS_PER_TICK && matchQueue->try_pop(std::ref(cmmd)); i++) {
            if (cmmd.code == CommandCode::_quit) {
                currentGame->QuitPlayer(cmmd.playerId);
            } else {
                currentGame->HandleCommand(cmmd);
            }
        }
        auto deltaTime = timeManager.updateTickTimer();
        currentGame->Update(deltaTime);
        broadcastGameMssg(std::make_shared<GameSnapshotSender>(currentGame->GetSnapshot()));
        timeManager.sleepIfNeeded();
    }
}

void GamesHandler::broadcastGameMssg(const std::shared_ptr<MessageSender>& message) {
    checkNumberPlayers();
    clientsQueues.applyToValues([&message](Queue<std::shared_ptr<MessageSender>>* clientQueue) {
        clientQueue->try_push(message);
    });
    checkNumberPlayers();
}

void GamesHandler::checkNumberPlayers() {
    if (currentPlayers == 0) {
        throw RunOutOfPlayers();
    }
}

std::string GamesHandler::getRandomLevel() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, config.getAvailableLevels().size() - 1);
    return config.getAvailableLevels()[dist(gen)];
}

void GamesHandler::clearQueue() {
    Command cmmd;
    while (matchQueue->try_pop(std::ref(cmmd))) {}
}
