#include "handlerGames.h"


#define MAX_CMMDS_PER_TICK 10
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
    // std::cout << "\n MATCH: Instanciando el game con " << playerIDs.size() << " jugadores\n";
    currentGame =
            std::make_unique<GameWorld>(Vector2D(INFINITY, INFINITY), playerIDs, getRandomLevel());
    broadcastGameMssg(std::make_shared<GameSceneSender>(std::move(currentGame->getSceneDto())));
    std::cout << "\n                HANDLER_Games: entering into a gameLoop\n";
    gameLoop();
    std::cout << "\n[1]             HANDLER_Games: getting out of the gameLoop\n";

    if (players.size() > NOT_ENOUGH_NUMBER_PLAYERS) {
        std::cout << "\n[2] HANDLER_Games: the size of 'players' es greater than "
                  << NOT_ENOUGH_NUMBER_PLAYERS << "...\n...So we areasking the game who won\n";
        PlayerID_t gameWinner = currentGame->WhoWon();

        std::cout << "\n[3] HANDLER_Games: We got who was the winner of the round\n";
        if (gameResults.find(gameWinner) != gameResults.end()) {
            int playerRecord = gameResults[gameWinner] += 1;
            std::cout << "\n[4] HANDLER_Games: We just updated the quantity of games won by the "
                         "player with id"
                      << gameWinner << "\n";
            if (playerRecord > recordGamesWon) {
                recordGamesWon = playerRecord;
            }
        } else {
            std::cout << "\n[4] HANDLER_Games: the winner that the game returned when asked was "
                         "never in the game\n";
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
