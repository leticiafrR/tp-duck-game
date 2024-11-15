#ifndef HANDLER_GAMES_
#define HANDLER_GAMES_

#include <atomic>
#include <iostream>
#include <memory>
#include <optional>
#include <random>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include "common/timeManager.h"
#include "model/Game.h"
#include "network/messageSender.h"

#include "config.h"
#include "matchStatus.h"

#define GAMES_TO_WIN_MATCH 5
#define GAMES_IN_GROUP 3
#define NOT_ENOUGH_NUMBER_PLAYERS 0


struct PlayerInfo {
    std::string nickName;
    // cppcheck-suppress unusedStructMember
    Queue<std::shared_ptr<MessageSender>>* senderQueue;
};


struct RunOutOfPlayers: public std::runtime_error {
    RunOutOfPlayers(): std::runtime_error("The match has no players to continue with. ") {}
};

class MessageSender;

class GamesHandler {
private:
    const std::vector<std::string> availableLevels;

    SafeMap<PlayerID_t, PlayerInfo>& players;

    Queue<Command>& commandQueue;

    int currentRecord = 0;
    PlayerID_t matchWinner = 0;

    bool existsMatchWinner = false;
    // o tal vez lo siguiente:
    MATCH_STATUS& matchStatus;


    // every time a player wins a game it gains a point
    std::unordered_map<PlayerID_t, int> playerPointsRecord;

    std::optional<GameWorld> currentGame;

    // private methods

    void checkNumberPlayers();

    void updateMatchWinnerStatus();

    void playOneGame();

    std::string getRandomLevel();

    void gameLoop();

    void broadcastGameMssg(const std::shared_ptr<MessageSender>& message);

    void registerGameWinnerPoint();

    void clearQueue();

public:
    GamesHandler(const Config& config, SafeMap<PlayerID_t, PlayerInfo>& players,
                 Queue<Command>& commandQueue, MATCH_STATUS& matchStatus);
    void playGroupOfGames();

    bool isThereFinalWinner();

    PlayerID_t whoWon();
};

#endif
