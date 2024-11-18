#include "match.h"

#include <cstdint>
#include <set>
#include <utility>
#include <vector>

#include "data/command.h"
#include "data/dataMatch.h"
#include "model/types.h"
#include "network/messageSender.h"

#include "gamesHandler.h"

#define MAX_COMMANDS 100
#define NO_WINNER_FORCED_END 0

Match::Match(const Config& config, PlayerID_t playerCreator):
        matchStatus(WAITING_PLAYERS),
        playerCreator(playerCreator),
        commandQueue(std::make_shared<Queue<Command>>(MAX_COMMANDS)),
        players(config.getMaxPlayers()),
        config(config) {}


bool Match::isAvailable() {
    return matchStatus == WAITING_PLAYERS && (config.getMaxPlayers() - players.size()) > 0;
}

bool Match::hasEnoughPlayers() { return players.size() >= config.getMinPlayers(); }

void Match::loadDataIfAvailble(std::vector<DataMatch>& availableMatches) {
    if (isAvailable()) {
        uint8_t currentPlayers = (uint8_t)players.size();
        PlayerInfo playerInfo;
        players.get(playerCreator, playerInfo);
        availableMatches.emplace_back(currentPlayers, (uint8_t)config.getMaxPlayers(),
                                      playerCreator, playerInfo.nickname);
    }
}

std::shared_ptr<Queue<Command>> Match::logInPlayer(PlayerID_t playerID,
                                                   const PlayerInfo& playerInfo) {
    if (isAvailable() && players.tryInsert(playerID, playerInfo)) {
        return commandQueue;
    }
    return nullptr;
}

/* Method that would be called by the senderThreads through the monitor of matches */
void Match::logOutPlayer(PlayerID_t idClient) {
    if (players.tryErase(idClient) && matchStatus == MATCH_ON_COURSE) {
        Command quit(CommandCode::_quit);
        quit.playerId = idClient;
        commandQueue->push(quit);
    }
}

void Match::run() {
    try {
        matchStatus = MATCH_ON_COURSE;
        auto playersData = assignSkins(config.getAvailableSkins());
        auto matchStartSender = std::make_shared<MatchStartSender>(
                std::move(playersData), Vector2D(Size::DUCK, Size::DUCK));
        broadcastMatchMssg(matchStartSender);
        GamesHandler gamesHandler(config, players, commandQueue, matchStatus);

        while (matchStatus == MATCH_ON_COURSE) {
            gamesHandler.playGroupOfGames();
        }

        auto winner = gamesHandler.whoWon();
        setEndOfMatch(winner);

    } catch (const ClosedQueue& q) {
    } catch (const RunOutOfPlayers& r) {}
}

bool Match::isOver() { return matchStatus == ENDED; }

void Match::forceEnd() { setEndOfMatch(NO_WINNER_FORCED_END); }

void Match::setEndOfMatch(PlayerID_t winner) {
    std::unique_lock<std::mutex> lock(endMatch);
    if (matchStatus != ENDED) {
        matchStatus = ENDED;
        try {
            commandQueue->close();
            if (players.size() != 0) {
                auto messageSender = std::make_shared<MatchExitSender>(winner);
                players.applyToValues([&messageSender](PlayerInfo& playerInfo) {
                    playerInfo.senderQueue->try_push(messageSender);
                    playerInfo.senderQueue->close();
                });
                players.clear();
            }
        } catch (const ClosedQueue& q) {
        } catch (const std::exception& e) {

        } catch (...) {}
    }
}

void Match::broadcastMatchMssg(const std::shared_ptr<MessageSender>& message) {
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

        assignation.emplace_back(playerID, skin, playerInfo.nickname);
        assignedSkins.insert(skin);
    });

    return assignation;
}
