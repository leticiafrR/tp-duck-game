#include "match.h"

Match::Match(Config& config, unsigned int numberPlayers):
        config(config),
        currentPlayers(0),
        numberPlayers(numberPlayers),
        commandQueue(MAX_COMMANDS),
        players(numberPlayers) {
    if (numberPlayers > config.getMaxPlayers()) {
        throw std::runtime_error(
                "ERROR: Too many players, can't manage a match with so many players.");
    }
}

/* method that will be called from the different Receivers threads. Has to be thread safe */
/* CONCURRENT ACCESS TO THE RESOURCE: MATCH (specifically to the attributes)*/

bool Match::logInPlayer(PlayerID_t idClient, const PlayerInfo& playerInfo) {
    std::unique_lock<std::mutex> lock(m);
    if (!players.tryInsert(idClient, playerInfo)) {
        return false;
    }
    currentPlayers++;
    if (currentPlayers == numberPlayers && !_is_alive) {
        this->start();
    }
    return true;
}

void Match::pushCommand(PlayerID_t idClient, const Command& cmmd) { commandQueue.push(cmmd); }

/*Method that wpuld be called concurrently (by the senderThreads) ante la desconexiòn de un jugador
 */
/*Quito acceso concurrente al modelo encolando el evento de salir de la partida para ser procesado
 * secuencialmente */
void Match::logOutPlayer(PlayerID_t idClient) {
    if (players.tryErase(idClient)) {
        Command quit;
        quit.playerID = idClient;

        /* Falta configurar un commandID para este comando */
        commandQueue.push(quit);
        currentPlayers--;
    }
}


void Match::run() {
    broadcastMatchMssg(std::make_shared<MatchStartSettings>(players, config.getAvailableSkins(),
                                                            config.getDuckSize()));
    HandlerGames handlerGames(config, players, commandQueue);
    while (!handlerGames.isThereFinalWinner()) {
        handlerGames.playGroupOfGames();
    }
    broadcastMatchMssg(std::make_shared<MatchResult>(handlerGames.whoWon()));
}

void Match::broadcastMatchMssg(const std::shared_ptr<ClientMessage>& message) {
    players.applyToItems([&message](PlayerID_t _, PlayerInfo& player) {
        try {
            player.senderQueue->try_push(message);
        } catch (const ClosedQueue& e) {
            /* The client has disconeccted, eventually will be taken out of the SafeMap players*/
        }
    });
}
