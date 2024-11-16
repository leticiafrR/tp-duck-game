#include "gamesHandler.h"


#define MAX_CMMDS_PER_TICK 10
#define TPS 20
#define ONE_PLAYER 1
// CREO QUE DEBERÌA DE RECIBIR UNA REFERENCIA? o tal vez solo le interesa al gamesHanlder (creo que
// sì)
//  tener un estado de ganado por default.(ahora creo que si deberìa ser un enum de la match, algo
//  como match status
//  -> mientras el estatus sea matchOncourse -> se sigue jugando, en cuanto se cammbia a ganado por
//  default o simplemente ganado -> se deja de jugar grupos de juegos)
GamesHandler::GamesHandler(const Config& config, SafeMap<PlayerID_t, PlayerInfo>& players,
                           Queue<Command>& commandQueue, std::atomic<MATCH_STATUS>& matchStatus):
        availableLevels(config.getAvailableLevels()),
        players(players),
        commandQueue(commandQueue),
        matchStatus(matchStatus) {
    auto playerIDs = players.getKeys();
    for (const auto& id: playerIDs) {
        playerPointsRecord[id] = 0;
    }
}

bool GamesHandler::isThereFinalWinner() { return existsMatchWinner; }

PlayerID_t GamesHandler::whoWon() { return matchWinner; }

void GamesHandler::playGroupOfGames() {

    for (int i = 0; i < GAMES_IN_GROUP && players.size() > NOT_ENOUGH_NUMBER_PLAYERS; i++) {

        playOneGame();
        // si el estado es ganado por default
        if (players.size() > ONE_PLAYER) {
            broadcastGameMssg(std::make_shared<GameEndingSender>(i == (GAMES_IN_GROUP - 1)));
        } else {
            broadcastGameMssg(std::make_shared<GameEndingSender>(true));
            break;
        }
    }

    updateMatchWinnerStatus();
    broadcastGameMssg(std::make_shared<GamesRecountSender>(playerPointsRecord, existsMatchWinner));
}

void GamesHandler::updateMatchWinnerStatus() {
    // si el estado es ganado por default solo seteo a existsMatchWinner como true, chequeo que
    // hayan jugadores, trato de conseguir el jugador ganador, checqueo jugadores, y determino a
    // este como ganador. retorno

    if (currentRecord >= GAMES_TO_WIN_MATCH) {
        for (auto it = playerPointsRecord.begin(); it != playerPointsRecord.end(); ++it) {
            /*first player found with that record*/
            if (!existsMatchWinner && it->second == currentRecord) {
                existsMatchWinner = true;
                matchWinner = it->first;
            } else if (existsMatchWinner && it->second == currentRecord) {
                /* second player found with that record-> there is no match winner*/
                existsMatchWinner = false;
                matchWinner = 0;
                break;
            }
        }
    }
}

void GamesHandler::playOneGame() {
    // cleaning the queue so it doesnt have commands left from the past game.
    clearQueue();

    auto playerIDs = players.getKeys();
    // verifying that we are not starting a game when we dont even have players
    checkNumberPlayers();
    currentGame = GameWorld(Vector2D(INFINITY, INFINITY), playerIDs, getRandomLevel());

    broadcastGameMssg(std::make_shared<GameSceneSender>(std::move(currentGame->getSceneDto())));
    gameLoop();

    registerGameWinnerPoint();
}


void GamesHandler::registerGameWinnerPoint() {
    // excepciòn si no hay ningun jugador
    checkNumberPlayers();
    PlayerID_t gameWinner = currentGame->WhoWon();

    if (players.size() > ONE_PLAYER) {
        if (playerPointsRecord.find(gameWinner) != playerPointsRecord.end()) {
            int playerRecord = playerPointsRecord[gameWinner] += 1;
            if (playerRecord > currentRecord) {
                currentRecord = playerRecord;
            }
        }
    } else {
        // Aquì podria setear un estado que indique que la partida se ganò por default en vez de
        // sumarle los puntos
        //  ojo: no dejar asi, para obtener el valor real de los games ganados por un jugador restar
        //  la cte. probablemente se deba corregir al momento de enviar el mensaje.
        currentRecord = playerPointsRecord[gameWinner] + 1;
        playerPointsRecord.clear();
        playerPointsRecord[gameWinner] = currentRecord;
        // matchStatus = wonByDefault;
    }
}

void GamesHandler::gameLoop() {

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

        auto deltaTime = timeManager.updateTickTimer();

        currentGame->Update(deltaTime);

        broadcastGameMssg(std::make_shared<GameUpdateSender>(currentGame->GetSnapshot()));

        timeManager.sleepIfNeeded();
    }
}


// methods that are not really complex

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
    while (commandQueue.try_pop(std::ref(cmmd))) {}
}
