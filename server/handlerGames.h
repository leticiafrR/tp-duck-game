#ifndef HANDLER_GAMES_
#define HANDLER_GAMES_

#include <memory>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#include "../common/command.h"
#include "../common/queue.h"
#include "../common/safeMap.h"
#include "model/gameWorld.h"

#include "clientMessages.h"
#include "config.h"

#define GAMES_TO_WIN_MATCH 10

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
    Queue<Command>& commandQueue;  // a un inicio es -1

    PlayerID_t matchWinner;
    std::unordered_map<PlayerID_t, int> gameResults;

    std::unique_ptr<GameWorld> currentGame;

public:
    HandlerGames(const Config& config, SafeMap<PlayerID_t, PlayerInfo>& players,
                 Queue<Command>& commandQueue);

    void playGroupOfGames();

    bool isThereFinalWinner();
    PlayerID_t whoWon();


private:
    void playOneGame();

    std::string getRandomLevel();

    std::string getThemeName(const std::string& level);

    void gameLoop();

    void broadcastGameMssg(const std::shared_ptr<ClientMessage>& message);
};

#endif
