#include "handlerGames.h"

#define MAX_CMMDS_PER_TICK 50
#define FPS 20
#define PRINT_TEST_OVERFLOW_TICK()                                                                 \
    std::cout << "Too many commds procesed in this tick! It overflowed the time assigned per tick" \
              << std::endl;


HandlerGames::HandlerGames(const Config& config, SafeMap<PlayerID_t, PlayerInfo>& players,
                           Queue<Command>& commandQueue, std::atomic<uint>& currentPlayers):
        availableLevels(config.getAvailableLevels()),
        players(players),
        commandQueue(commandQueue),
        currentPlayers(currentPlayers) {

    auto playerIDs = players.getKeys();
    for (auto& id: playerIDs) {
        gameResults[id] = 0;
    }
}

bool HandlerGames::isThereFinalWinner() { return existsMatchWinner; }
PlayerID_t HandlerGames::whoWon() { return matchWinner; }

void HandlerGames::playGroupOfGames() {
    for (int i = 0; i < 5; i++) {
        // decido parar todo si ya no hay ningun jugador
        // en el futuro tambièn serìa si es que solo queda  un juagdor
        if (currentPlayers == 0) {
            return;
        }
        playOneGame();
    }

    /* sending the recount of the games won by each player*/
    broadcastGameMssg(std::make_shared<GamesRecount>(gameResults, existsMatchWinner));

    /* loking if there is a matchWinner*/
    if (recordGamesWon >= GAMES_TO_WIN_MATCH) {
        /* if the record is greater than the necesary to win a match we look if there is just one
         * player with that number of games won. If not there is not a matchWinner*/
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

void HandlerGames::playOneGame() {
    auto level = getRandomLevel();

    auto theme = getThemeName(level);  // retorna una copia independiente
    currentGame = std::make_unique<GameWorld>(level, players.getKeys());

    /*sending the initial setting of the game*/
    broadcastGameMssg(std::make_shared<GameStartSettings>(
            std::move(theme),
            std::ref(currentGame->getGamePlatforms())));  // respecto al gamePlatforms, este no
                                                          // cambiarìa durante el game -> no es
                                                          // necesario que se copie, podemos
                                                          // trabajar con una referencia. Supongo
                                                          // que me dan una referencia. (no deberìa
                                                          // de cambiar) (no queremos que haya
                                                          // acceso de lecto escritura concurrente)
    gameLoop();
    PlayerID_t gameWinner = currentGame->whoWon();
    int playerRecord = gameResults[gameWinner] += 1;
    if (playerRecord > recordGamesWon) {
        recordGamesWon = playerRecord;
    }
}


void HandlerGames::gameLoop() {

    TimeManager timeManager(FPS);

    while (!currentGame->hasWinner()) {

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

void HandlerGames::broadcastGameMssg(const std::shared_ptr<ClientMessage>& message) {
    players.applyToItems([&message](PlayerID_t _, PlayerInfo& player) {
        try {
            player.senderQueue->try_push(message);
        } catch (const ClosedQueue& e) {
            /* The client has disconeccted, eventually will be taken out of the SafeMap players*/
        }
    });
}

std::string HandlerGames::getRandomLevel() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, availableLevels.size() - 1);
    return availableLevels[dist(gen)];
}

std::string HandlerGames::getThemeName(const std::string& level) {
    // EJEMPLO DE TEST-> luego se deberìa obtener el cotenido del archivo yaml de nombre level
    return "dark";
}
