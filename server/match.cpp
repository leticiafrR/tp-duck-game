#include "match.h"

#include <cstdint>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/playerIdentifier.h"
#include "data/command.h"
#include "data/dataMatch.h"
#include "data/errorCodesJoinMatch.h"
#include "model/types.h"
#include "network/messageSender.h"

#include "gamesHandler.h"

#define MAX_COMMANDS 100
#define NO_WINNER_FORCED_END 0

// OJO:ya no sirve de mucho el tope de clientsQueues. NO INDICA UN LIMITE REAL,
Match::Match(const Config& config, uint16_t matchHost):
        matchStatus(WAITING_PLAYERS),
        matchHost(matchHost),
        matchQueue(std::make_shared<Queue<Command>>(MAX_COMMANDS)),
        clientsQueues(config.getMaxPlayers()),
        playersPerClient(config.getMaxPlayers()),
        config(config) {}

void Match::loadDataIfAvailble(std::vector<DataMatch>& availableMatches) {
    if (isAvailable()) {
        ClientInfo infoCreator;
        playersPerClient.get(matchHost, infoCreator);
        availableMatches.emplace_back(currentPlayers, (uint8_t)config.getMaxPlayers(), matchHost,
                                      infoCreator.baseNickname);
    }
}

// debe de actualizar ambos safemaps
// DEBE ACTUALIZAR CURRENT PLAYERS
std::shared_ptr<Queue<Command>> Match::logInClient(
        const ClientInfo& connectionInfo, Queue<std::shared_ptr<MessageSender>>* clientQueue,
        uint8_t& eCode) {

    if (matchStatus != WAITING_PLAYERS) {
        eCode = E_CODE::ALREADY_STARTED;
        return nullptr;
    }
    if ((config.getMaxPlayers() - currentPlayers) == 0) {
        eCode = E_CODE::NOT_ENOUGH_SPOTS;
        return nullptr;
    }
    clientsQueues.tryInsert(connectionInfo.connectionId, clientQueue);
    playersPerClient.tryInsert(connectionInfo.connectionId, connectionInfo);
    currentPlayers += connectionInfo.playersPerConnection;

    return matchQueue;
}

// DEBE ACTUALIZAR CURRENT PLAYERS
void Match::logOutClient(uint16_t connectionID) {
    clientsQueues.tryErase(connectionID);

    ClientInfo playersInClient;
    playersPerClient.get(connectionID, playersInClient);

    if (matchStatus == MATCH_ON_COURSE) {
        for (uint8_t i = 0; i < playersInClient.playersPerConnection; i++) {
            Command quit(CommandCode::_quit, i,
                         PlayerIdentifier::GeneratePlayerID(connectionID, i));
            matchQueue->push(quit);
        }
    }
    currentPlayers -= playersInClient.playersPerConnection;
    playersPerClient.tryErase(connectionID);
}

void Match::run() {
    _hadStarted = true;
    matchStatus = MATCH_ON_COURSE;
    try {
        auto playersData = assignSkins(config.getAvailableSkins());
        auto matchStartSender = std::make_shared<MatchStartSender>(
                std::move(playersData), Vector2D(Size::DUCK, Size::DUCK));

        broadcastMatchMssg(matchStartSender);
        GamesHandler gamesHandler(config, clientsQueues, playersPerClient, matchQueue, matchStatus,
                                  currentPlayers);

        while (matchStatus == MATCH_ON_COURSE) {
            gamesHandler.playGroupOfGames();
        }

        auto winner = gamesHandler.whoWon();
        setEndOfMatch(winner);

    } catch (const ClosedQueue& q) {
    } catch (const RunOutOfPlayers& r) {}
}

void Match::forceEnd() { setEndOfMatch(NO_WINNER_FORCED_END); }

void Match::setEndOfMatch(PlayerID_t winner) {
    std::unique_lock<std::mutex> lock(endMatch);
    if (matchStatus != ENDED) {
        matchStatus = ENDED;
        matchQueue->close();
        if (clientsQueues.size() != 0) {

            auto messageSender = std::make_shared<MatchExitSender>(winner);

            clientsQueues.applyToValues(
                    [&messageSender](Queue<std::shared_ptr<MessageSender>>* clientQueue) {
                        clientQueue->try_push(messageSender);
                        clientQueue->close();
                    });

            clientsQueues.clear();
            playersPerClient.clear();
        }
    }
}

void Match::broadcastMatchMssg(const std::shared_ptr<MessageSender>& message) {
    checkNumberPlayers();
    clientsQueues.applyToValues([&message](Queue<std::shared_ptr<MessageSender>>* clientQueue) {
        clientQueue->try_push(message);
    });
    checkNumberPlayers();
}

void Match::checkNumberPlayers() {
    if (currentPlayers == 0) {
        throw RunOutOfPlayers();
    }
}

std::vector<PlayerData> Match::assignSkins(int numberSkins) {
    checkNumberPlayers();
    if (currentPlayers > numberSkins) {
        throw std::invalid_argument("ERROR: When Match is try to make an assignation of skins "
                                    "there are too many players!");
    }
    std::unordered_set<int> availableSkins;
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < numberSkins; i++) {
        availableSkins.emplace(i);
    }

    std::vector<PlayerData> assignation;
    playersPerClient.applyToItems(
            [&availableSkins, &assignation](uint16_t connectionID, const ClientInfo& clientInfo) {
                for (uint8_t i = 0; i < clientInfo.playersPerConnection; i++) {
                    int randomIndex = std::rand() % availableSkins.size();
                    auto it = availableSkins.begin();
                    std::advance(it, randomIndex);

                    PlayerID_t playerID = PlayerIdentifier::GeneratePlayerID(connectionID, i);
                    std::stringstream nickname;
                    nickname << clientInfo.baseNickname << "(" << (int)i << ")";
                    assignation.emplace_back(playerID, *it, nickname.str());
                    availableSkins.erase(it);
                }
            });
    return assignation;
}

// si al menos un jugador màs puede entrar a la partida
bool Match::isAvailable() {
    return matchStatus == WAITING_PLAYERS && (config.getMaxPlayers() - currentPlayers) > 0;
}
bool Match::readyToStart() { return currentPlayers >= config.getMinPlayers(); }
bool Match::isOver() { return matchStatus == ENDED; }
bool Match::hadStarted() { return _hadStarted; }
