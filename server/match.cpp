#include "match.h"

#include <exception>
#include <iostream>

#include "model/types.h"

#define MAX_COMMANDS 100
#define NO_WINNER_FORCED_END 0
// si se tiene menos de esta cantidad o igual se pararà de jugar màs partidas

// The monitor must be sure that the number Players is smaller than the MAX
Match::Match(Config& config, int numberPlayers, PlayerID_t playerCreator):
        playerCreator(playerCreator),
        numberPlayers(numberPlayers),
        commandQueue(MAX_COMMANDS),
        players(numberPlayers),
        config(config),
        status(WAITING_PLAYERS) {
    if (numberPlayers > config.getMaxPlayers()) {
        throw std::runtime_error(
                "ERROR: Too many players, can't manage a match with so many players.");
    }
}

int Match::missingPlayers() { return numberPlayers - players.size(); }

Queue<Command>& Match::logInPlayer(PlayerID_t idPlayer, const PlayerInfo& playerInfo) {
    if (!players.tryInsert(idPlayer, playerInfo)) {
        std::stringstream mssg_error;
        mssg_error << "Error: Trying to include player [ID]: " << idPlayer
                   << " into the match [ID]: " << playerCreator
                   << " when the match has already started.";
        throw std::runtime_error(mssg_error.str());
    }
    return commandQueue;
}

/* Method that would be called concurrently (by the senderThreads) when the sender thread of the
 * client notices the disconection. Wont be called if the match is the one who killed all its
 * players */
void Match::logOutPlayer(PlayerID_t idClient) {
    players.tryErase(idClient);
    if (_is_alive) {
        // if the match is alive the player could be part of a game world. If not yet
        Command quit(CommandCode::_quit);
        quit.playerId = idClient;
        commandQueue.push(quit);
    }
}


void Match::run() {
    status = MATCH_ON_COURSE;
    try {

        auto playersData = assignSkins(config.getAvailableSkins());
        broadcastMatchMssg(std::make_shared<MatchStartSender>(std::move(playersData),
                                                              Vector2D(Size::DUCK, Size::DUCK)));

        GamesHandler gamesHandler(config, players, commandQueue, std::ref(status));

        while (!gamesHandler.isThereFinalWinner() && players.size() > NOT_ENOUGH_NUMBER_PLAYERS) {
            gamesHandler.playGroupOfGames();
        }

        auto winner = gamesHandler.whoWon();
        setEndOfMatch(winner);

    } catch (const ClosedQueue& q) {
        // forceEnd of the match may generate this exception.
    } catch (const RunOutOfPlayers& r) {
        // forceEnd of the match may generate to try to do a broadcast over no players
    }
    std::cout << "El hilo de la match terminò!\n";
}

void Match::forceEnd() { setEndOfMatch(NO_WINNER_FORCED_END); }

void Match::setEndOfMatch(PlayerID_t winner) {
    // only makes sence to do this operation if there are more than 0 players.
    // and also in this way i know that im not doing this twice.
    try {
        commandQueue.close();
        std::unique_lock<std::mutex> lock(m);  // creo que este metodo al ser usado tanto por codigo
                                               // ajeno (cuando el acceptor) como por
        if (players.size() != 0) {
            auto messageSender = std::make_shared<MatchExitSender>(winner);
            players.applyToValues([&messageSender](PlayerInfo& playerInfo) {
                // CREO QUE ESTE PUSH SÌ DEBERÌA DE SER BLOQUEANTE
                playerInfo.senderQueue->push(messageSender);
                playerInfo.senderQueue->close();
            });
            players.clear();
        }
    } catch (const ClosedQueue& q) {
        std::cout << "[Match: wen trying to end the match]:  youre trying to close a queue that is "
                     "already closed\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "[Match: wen trying to end the match]:" << e.what() << std::endl;
    } catch (...) {
        std::cout << "[Match: wen trying to end the match]: The is an uknow exception!!\n";
    }
}

void Match::broadcastMatchMssg(const std::shared_ptr<MessageSender>& message) {
    // want to interrumpt the game if there are no players and ia notice that
    checkNumberPlayers();
    players.applyToValues(
            [&message](PlayerInfo& player) { player.senderQueue->try_push(message); });
    checkNumberPlayers();
}

void Match::checkNumberPlayers() {
    if (players.size() == 0) {
        throw RunOutOfPlayers();
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
