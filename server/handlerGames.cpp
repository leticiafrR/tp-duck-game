#include "handlerGames.h"

#include "../common/timeManager.h"

#define MAX_CMMDS_PER_TICK 50
#define FPS 10
#define PRINT_TEST_OVERFLOW_TICK()                                                                 \
    std::cout << "Too many commds procesed in this tick! It overflowed the time assigned per tick" \
              << std::endl;


HandlerGames::HandlerGames(const Config& config, SafeMap<PlayerID_t, PlayerInfo>& players,
                           Queue<Command>& commandQueue):
        availableLevels(config.getAvailableLevels()),
        players(players),
        commandQueue(commandQueue),
        matchWinner(0) {
    auto playerIDs = players.getKeys();
    for (auto& id: playerIDs) {
        gameResults[id] = 0;
    }
}

void HandlerGames::playGroupOfGames() {
    for (int i = 0; i < 5; i++) {
        playOneGame();
    }
    /* sending the recount of the games won by each player*/
    broadcastGameMssg(std::make_shared<GamesRecount>(gameResults));
}

void HandlerGames::playOneGame() {
    auto level = getRandomLevel();
    auto theme = getThemeName(level);
    currentGame = std::make_unique<GameWorld>(level, players.getKeys());

    /*sending the initial setting of the game*/
    broadcastGameMssg(std::make_shared<GameStartSettings>(theme, currentGame->getGamePlatforms()));

    gameLoop();
    gameResults[currentGame->whoWon()] += 1;
}


void HandlerGames::gameLoop() {

    TimeManager timeManager(FPS);
    while (!currentGame->hasWinner()) {
        if (timeManager.synchronizeTick() < std::chrono::duration<double, std::milli>(0)) {
            PRINT_TEST_OVERFLOW_TICK();
        }

        int countCommands = 0;
        Command cmmd;
        while (countCommands < MAX_CMMDS_PER_TICK && commandQueue.try_pop(std::ref(cmmd))) {
            currentGame->handleCommand(cmmd);
            countCommands++;
        }
        currentGame->update();
        broadcastGameMssg(std::make_shared<GameUpdate>(currentGame->getSnapshoot()));
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
    return "bosque";
}
