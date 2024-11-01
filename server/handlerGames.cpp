#include "handlerGames.h"

HandlerGames::HandlerGames(const Config& config, SafeMap<PlayerID_t, PlayerInfo>& players,
                           Queue<Command>& commandQueue):
        availableLevels(config.getAvailableLevels()),
        players(players),
        commandQueue(commandQueue),
        matchWinner(0) {}

void HandlerGames::playGroupOfGames() {
    for (int i = 0; i < 5; i++) {
        playOneGame();
    }
    // aqui envia el recuento/marcador de las rondas
}

void HandlerGames::playOneGame() {
    auto level = getRandomLevel();
    auto theme = getThemeName(level);
    currentGame = std::make_unique<GameWorld>(level, players.getKeys());

    /*sending the initial setting of the game*/
    broadcastGameMssg(std::make_shared<GameStartSettings>(theme, currentGame->getGamePlatforms()));

    /* during a game*/
    gameLoop();

    // /*sending the winner of the game*/
    // broadcastGameMssg(std::make_shared<GameResult>(currentGame->whoWon()));
}


void HandlerGames::gameLoop() {
    // deberìa de enviar 10 frames por segundo... o a 60 jejejje
    while (!currentGame->hasWinner()) {
        // envio snapshoots { posicones..., bool hasWinner}
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
