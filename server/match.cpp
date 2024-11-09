#include "match.h"

#include "model/types.h"

#define NO_WINNER_FORCED_END 0
// si se tiene menos de esta cantidad o igual se pararà de jugar màs partidas

Match::Match(Config& config, int numberPlayers):
        numberPlayers(numberPlayers),
        commandQueue(MAX_COMMANDS),
        players(numberPlayers),
        config(config) {
    if (numberPlayers > config.getMaxPlayers()) {
        throw std::runtime_error(
                "ERROR: Too many players, can't manage a match with so many players.");
    }
}

/* method that will be called from the different Receivers threads. Has to be thread safe */
bool Match::logInPlayer(PlayerID_t idClient, const PlayerInfo& playerInfo) {
    std::unique_lock<std::mutex> lock(m);
    if (!players.tryInsert(idClient, playerInfo)) {
        return false;
    }
    if ((int)players.size() == numberPlayers && !_is_alive) {
        this->start();
    }
    return true;
}

// will be closed when the match is over. If someone tries to push a commd it will throw an
// exception (CosedQueue)
void Match::pushCommand(const Command& cmmd) { commandQueue.push(cmmd); }

/*Method that would be called concurrently (by the senderThreads) when the sender thread of the
 * client notices the disconection */
void Match::logOutPlayer(PlayerID_t idClient) {
    if (players.tryErase(idClient)) {
        Command quit(CommandCode::_quit);
        quit.playerId = idClient;
        // eventually it will be removed from the current game but it is already removed from the
        // list to which the match make the broadcasts.
        commandQueue.push(quit);
    }
}
std::vector<PlayerData> Match::assignSkins(int numberSkins) {
    checkNumberPlayers();
    // Generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, numberSkins - 1);

    std::set<int> assignedSkins;
    std::vector<PlayerData> assignation;

    players.applyToItems([&assignedSkins, &assignation, &gen, &dis](PlayerID_t playerID,
                                                                    PlayerInfo& playerInfo) {
        int skin;
        do {
            skin = dis(gen);
        } while (assignedSkins.find(skin) != assignedSkins.end());

        assignation.emplace_back(playerID, skin, playerInfo.nickName);
        assignedSkins.insert(skin);
    });
    return assignation;
}

void Match::run() {
    try {

        auto playersData = assignSkins(config.getAvailableSkins());

        broadcastMatchMssg(std::make_shared<MatchStartSender>(std::move(playersData),
                                                              Vector2D(Size::DUCK, Size::DUCK)));

        HandlerGames handlerGames(config, players, commandQueue);

        while (!handlerGames.isThereFinalWinner() && players.size() > NOT_ENOUGH_NUMBER_PLAYERS) {
            handlerGames.playGroupOfGames();
        }

        setEndOfMatch(handlerGames.whoWon());

    } catch (const ClosedQueue& q) {
        // forceEnd of the match may generate this exception.
    } catch (const RunOutOfPlayers& r) {
        // forceEnd of the match may generate to try to do a broadcast over no players
    }
}

void Match::forceEnd() { setEndOfMatch(NO_WINNER_FORCED_END); }

void Match::setEndOfMatch(PlayerID_t winner) {
    // only makes sence to do this operation if there are more than 0 players.
    // and also in this way i know that im not doing this twice.
    try {
        commandQueue.close();
    } catch (const ClosedQueue& q) {}

    std::unique_lock<std::mutex> lock(m);
    if (players.size() != 0) {
        auto messageSender = std::make_shared<MatchExitSender>(winner);
        players.applyToValues([&messageSender](PlayerInfo& playerInfo) {
            // CREO QUE ESTE PUSH SÌ DEBERÌA DE SER BLOQUEANTE
            playerInfo.senderQueue->push(messageSender);
            playerInfo.senderQueue->close();
        });
        players.clear();
    }
}

void Match::checkNumberPlayers() {
    if (players.size() == 0) {
        throw RunOutOfPlayers();
    }
}
void Match::broadcastMatchMssg(const std::shared_ptr<MessageSender>& message) {
    // want to interrumpt the game if there are no players and ia notice that
    checkNumberPlayers();
    players.applyToValues(
            [&message](PlayerInfo& player) { player.senderQueue->try_push(message); });
    checkNumberPlayers();
}
