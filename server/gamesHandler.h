#ifndef HANDLER_GAMES_
#define HANDLER_GAMES_

#include <atomic>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/safeMap.h"
#include "model/Game.h"

#include "config.h"
#include "matchStatus.h"
#include "playerInfo.h"


#define NOT_ENOUGH_NUMBER_PLAYERS 0


struct RunOutOfPlayers: public std::runtime_error {
    RunOutOfPlayers(): std::runtime_error("The match has no players to continue with. ") {}
};

class MessageSender;

class GamesHandler {
private:
    const std::vector<std::string> availableLevels;

    SafeMap<PlayerID_t, PlayerInfo>& players;

    std::shared_ptr<Queue<Command>> commandQueue;

    int currentRecord = 0;
    PlayerID_t matchWinner = 0;

    std::atomic<MATCH_STATUS>& matchStatus;

    std::unordered_map<PlayerID_t, int> playerPointsRecord;

    std::optional<GameWorld> currentGame;

    const Config& config;

public:
    GamesHandler(const Config& config, SafeMap<PlayerID_t, PlayerInfo>& players,
                 std::shared_ptr<Queue<Command>> commandQueue,
                 std::atomic<MATCH_STATUS>& matchStatus);
    void playGroupOfGames();

    PlayerID_t whoWon();

private:
    void checkNumberPlayers();

    void updateMatchWinnerStatus();

    void playOneGame();

    std::string getRandomLevel();

    void gameLoop();

    void broadcastGameMssg(const std::shared_ptr<MessageSender>& message);

    void registerGameWinnerPoint();

    void clearQueue();
};

#endif
