#ifndef HANDLER_GAMES_
#define HANDLER_GAMES_

#include <atomic>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../common/queue.h"
#include "../common/safeMap.h"
#include "../common/timeManager.h"
#include "model/gameWorld.h"

#include "config.h"
#include "messageSender.h"

#define GAMES_TO_WIN_MATCH 10
#define NOT_ENOUGH_NUMBER_PLAYERS 0

struct RunOutOfPlayers: public std::runtime_error {
    RunOutOfPlayers(): std::runtime_error("The match has no players to continue with. ") {}
};

class HandlerGames {
private:
    const std::vector<std::string> availableLevels;
    /* used to set the number of participants in the game at
     * its begginging (we get it keys)*/
    /* And also to send to the clients the escenario of the
     * game that is going to start*/

    /* Used during each Game to send the updates*/

    /* ¿And finally used when the Game is over to communicate
     * who was the winner of it?<---- NOT SURE */
    SafeMap<PlayerID_t, PlayerInfo>& players;

    /* Used during each Game*/
    /* The match thread give us a reference to its
     * command queue to process the commands in each
     * Game*/
    Queue<Command>& commandQueue;

    int recordGamesWon = 0;
    PlayerID_t matchWinner = 0;
    bool existsMatchWinner = false;

    std::unordered_map<PlayerID_t, int> gameResults;

    std::unique_ptr<GameWorld> currentGame;

public:
    HandlerGames(const Config& config, SafeMap<PlayerID_t, PlayerInfo>& players,
                 Queue<Command>& commandQueue);

    void playGroupOfGames();

    bool isThereFinalWinner();
    PlayerID_t whoWon();


private:
    void checkNumberPlayers();
    /* if the record of games won by a player is greater than the necesary to win a match we look if
     * there is just one player with that number of games won. If there is just one: found the match
     * winner! */
    void updateMatchWinnerStatus();

    void playOneGame();

    std::string getRandomLevel();

    std::string getThemeName(const std::string& level);

    void gameLoop();

    void broadcastGameMssg(const std::shared_ptr<MessageSender>& message);
};

#endif
