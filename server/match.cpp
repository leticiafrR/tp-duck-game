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

// will be closed when the match is over. If someone tries to push a commd it will throw an
// exception (CosedQueue)
void Match::pushCommand(PlayerID_t idClient, const Command& cmmd) { commandQueue.push(cmmd); }

/*Method that wpuld be called concurrently (by the senderThreads) when the sender thread of the
 * client notices the disconection */
void Match::logOutPlayer(PlayerID_t idClient) {
    if (players.tryErase(idClient)) {
        Command quit(MESSAGE_TYPE::CONTROL_MATCH_STATE, CONTROL_MATCH_STATE::QUIT_MATCH);
        quit.playerID = idClient;
        // eventually it will be removed from the current game but it is already removed from the
        // list to which the match make the broadcasts.
        commandQueue.push(quit);
        currentPlayers--;
    }
}


void Match::run() {
    broadcastMatchMssg(std::make_shared<MatchStartSettings>(players, config.getAvailableSkins(),
                                                            config.getDuckSize()));
    HandlerGames handlerGames(config, players, commandQueue, currentPlayers);
    while (!handlerGames.isThereFinalWinner() && currentPlayers != 0) {
        handlerGames.playGroupOfGames();
    }
    broadcastMatchMssg(std::make_shared<MatchResult>(handlerGames.whoWon()));
    // match is forcing their clients threads to end
    commandQueue.close();
    players.applyToItems(
            [](PlayerID_t _, PlayerInfo& playerInfo) { playerInfo.senderQueue->close(); });
}

void Match::broadcastMatchMssg(const std::shared_ptr<ClientMessage>& message) {
    players.applyToItems([&message](PlayerID_t _, PlayerInfo& player) {
        player.senderQueue->try_push(message);
        // this do not throws a exeption, bacause the clients do not close therir queues. I do it
    });
}
