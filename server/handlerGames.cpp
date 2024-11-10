#include "handlerGames.h"


#define MAX_CMMDS_PER_TICK 50
#define TPS 20
// #define PRINT_TEST_OVERFLOW_TICK()
//     std::cout << "Too many commds procesed in this tick! It overflowed the time assigned per
//     tick"
//               << std::endl;
#define GAMES_IN_GROUP 5

HandlerGames::HandlerGames(const Config& config, SafeMap<PlayerID_t, PlayerInfo>& players,
                           Queue<Command>& commandQueue):
        availableLevels(config.getAvailableLevels()), players(players), commandQueue(commandQueue) {
    auto playerIDs = players.getKeys();
    for (auto& id: playerIDs) {
        gameResults[id] = 0;
    }
}

bool HandlerGames::isThereFinalWinner() { return existsMatchWinner; }

PlayerID_t HandlerGames::whoWon() { return matchWinner; }

void HandlerGames::playGroupOfGames() {
    for (int i = 0; i < GAMES_IN_GROUP && players.size() > NOT_ENOUGH_NUMBER_PLAYERS; i++) {
        playOneGame();
        broadcastGameMssg(std::make_shared<GameEndingSender>(i == (GAMES_IN_GROUP - 1)));
    }
    broadcastGameMssg(std::make_shared<GamesRecountSender>(gameResults, existsMatchWinner));
    updateMatchWinnerStatus();
}

void HandlerGames::playOneGame() {
    auto playerIDs = players.getKeys();
    checkNumberPlayers();
    std::cout << "\n MATCH:Iniciando el game con " << playerIDs.size() << " jugadores\n";
    currentGame =
            std::make_unique<GameWorld>(Vector2D(INFINITY, INFINITY), playerIDs, getRandomLevel());
    broadcastGameMssg(std::make_shared<GameSceneSender>(std::move(currentGame->getSceneDto())));

    gameLoop();

    if (players.size() > NOT_ENOUGH_NUMBER_PLAYERS) {
        PlayerID_t gameWinner = currentGame->WhoWon();
        int playerRecord = gameResults[gameWinner] += 1;
        if (playerRecord > recordGamesWon) {
            recordGamesWon = playerRecord;
        }
    }
}

void HandlerGames::gameLoop() {
    TimeManager timeManager(TPS);

    while (!currentGame->IsOver() && players.size() > NOT_ENOUGH_NUMBER_PLAYERS) {
        Command cmmd;
        for (int i = 0; i < MAX_CMMDS_PER_TICK && commandQueue.try_pop(std::ref(cmmd)); i++) {
            if (cmmd.cmd == CommandCode::_quit)
                // currentGame->quitPlayer(cmmd.playerId);
                continue;
            else
                currentGame->HandleCommand(cmmd);
        }


        // if (delta < std::chrono::duration<double, std::milli>(0))
        // PRINT_TEST_OVERFLOW_TICK();

        currentGame->Update(0.05);
        broadcastGameMssg(std::make_shared<GameUpdateSender>(currentGame->GetSnapshot()));
        auto delta = timeManager.synchronizeTick();
    }
}

void HandlerGames::broadcastGameMssg(const std::shared_ptr<MessageSender>& message) {
    checkNumberPlayers();
    players.applyToValues(
            [&message](PlayerInfo& player) { player.senderQueue->try_push(message); });
    checkNumberPlayers();
}

void HandlerGames::checkNumberPlayers() {
    if (players.size() == 0) {
        throw RunOutOfPlayers();
    }
}

std::string HandlerGames::getRandomLevel() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, availableLevels.size() - 1);
    return availableLevels[dist(gen)];
}

void HandlerGames::updateMatchWinnerStatus() {
    if (recordGamesWon >= GAMES_TO_WIN_MATCH) {
        for (auto it = gameResults.begin(); it != gameResults.end(); ++it) {
            /*first player found with that record*/
            if (!existsMatchWinner && it->second == recordGamesWon) {
                existsMatchWinner = true;
                matchWinner = it->first;
            } else if (existsMatchWinner && it->second == recordGamesWon) {
                /* second player found with that record-> there is no match winner*/
                existsMatchWinner = false;
                matchWinner = 0;
                break;
            }
        }
    }
}
