#include "handlerGames.h"

#define MAX_CMMDS_PER_TICK 50
#define FPS 20
#define PRINT_TEST_OVERFLOW_TICK()                                                                 \
    std::cout << "Too many commds procesed in this tick! It overflowed the time assigned per tick" \
              << std::endl;
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

// NOTE: we never got here if the gameResults map was initialized empty.
void HandlerGames::playGroupOfGames() {
    for (int i = 0; i < GAMES_IN_GROUP && players.size() > NOT_ENOUGH_NUMBER_PLAYERS; i++) {
        playOneGame();
    }
    /* sending the recount of the games won by each player*/
    broadcastGameMssg(std::make_shared<GamesRecount>(gameResults, existsMatchWinner));
    /* loking if there is a final matchWinner*/
    updateMatchWinnerStatus();
}
// acabo de hacer un review de que pasarìa en un apartida (grupos de games) si es que ya se
// concretizò un forcedEnd nota creo que todas las veces que me fijè en el numero de currentplayers
// deberìa fijarme en el size de players porque podrìa generar race conditions

void HandlerGames::playOneGame() {
    auto level = getRandomLevel();

    auto playerIDs = players.getKeys();
    // cppcheck-suppress unsignedLessThanZero
    if (playerIDs.size() <= NOT_ENOUGH_NUMBER_PLAYERS) {
        return;
    }
    // instanciamos un game que sì o sì tiene suficientes jugadores
    // leticia estaba preguntando si es que es necesario tener el gameWorld en el heap.
    currentGame = std::make_unique<GameWorld>(level, playerIDs);

    /*sending the initial setting of the game*/
    // Si es que ya se cerraron las queues seguro que salta excepciòn
    // al objeto que està en el heap le doy a su completo uso un objeto que sea movible
    auto gameSceneDto = currentGame->getSceneDto();
    broadcastGameMssg(std::make_shared<GameStartSettings>(std::move(gameSceneDto)));

    gameLoop();  // if this throws us an exeption this means that the match is forcing the game to
                 // end

    if (players.size() > NOT_ENOUGH_NUMBER_PLAYERS) {
        // this means that we went out of the gameLoop because there is a game winner
        PlayerID_t gameWinner = currentGame->whoWon();
        int playerRecord = gameResults[gameWinner] += 1;
        if (playerRecord > recordGamesWon) {
            recordGamesWon = playerRecord;
        }
    }
}


void HandlerGames::gameLoop() {

    TimeManager timeManager(FPS);

    // believe that here  should check the number if the current players too
    while (!currentGame->hasWinner() && players.size() > NOT_ENOUGH_NUMBER_PLAYERS) {

        if (timeManager.synchronizeTick() < std::chrono::duration<double, std::milli>(0)) {
            PRINT_TEST_OVERFLOW_TICK();
        }

        int countCommands = 0;
        Command cmmd(0, 0);
        while (countCommands < MAX_CMMDS_PER_TICK && commandQueue.try_pop(std::ref(cmmd))) {
            if (cmmd.commandID == CONTROL_MATCH_STATE::QUIT_MATCH) {
                currentGame->quitPlayer(cmmd.playerID);
            } else {
                currentGame->handleCommand(cmmd);
                countCommands++;
            }
        }

        currentGame->update();

        broadcastGameMssg(std::make_shared<GameUpdate>(currentGame->getSnapshot()));
    }
}

// if this throws us a exception it means that the match is who is trying to kill all of its clients
// so it should stop all the current game.
void HandlerGames::broadcastGameMssg(const std::shared_ptr<MessageSender>& message) {
    checkNumberPlayers();
    players.applyToItems([&message](PlayerID_t _, PlayerInfo& player) {
        player.senderQueue->try_push(message);
    });
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
