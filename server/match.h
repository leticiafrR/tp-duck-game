#ifndef MATCH_H
#define MATCH_H

#include <atomic>
#include <iostream>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "common/thread.h"
#include "data/id.h"

#include "gamesHandler.h"


class Match: public Thread {
private:
    std::atomic<MATCH_STATUS> matchStatus;
    std::condition_variable waitingPlayers;
    std::mutex m;
    // aqui deberìa de haber un mutex

    // used as the id of the match
    PlayerID_t playerCreator;

    std::shared_ptr<Queue<Command>> commandQueue;

    SafeMap<PlayerID_t, PlayerInfo> players;

    Config& config;

    std::mutex endMatch;

public:
    /* Builds the match with a tolerance of players as the object config indicates. */
    explicit Match(Config& config, PlayerID_t playerCreator);

    /* Returns the number of players missing to start the game, so the monitor can start this when
     * logging the player that fulls the match */
    int openSpots();

    /* Method that must be called when the missing players != 0. If the Match has
     * already started the method will throw an exception, else it will include the playerInfo into
     * the container with wich players are going to receive the broadcasts and will return the queue
     * of commands that the match is going to process */
    /* Method called by the Lobby of each player-> CONCURRENT ACCES that must be handled by the
     * monitor*/
    std::shared_ptr<Queue<Command>> logInPlayer(PlayerID_t idClient, const PlayerInfo& playerInfo);

    void waitForMatchStarting(PlayerID_t idClient);

    /* This method takes out of the container with the players to broadcast the queue of the client
     * with the ID received. It means that it is called when the client in the middle of the match
     * has disconected (the sender thread reconizes that the client has disconnected and
     * calles this method-> CONCURRENT ACCESS that must be handled by the monitor) */

    /* SnapShoots to the disconnected client and also it should take off the player of the WorldMap
     * (if hasnt end)*/
    void logOutPlayer(PlayerID_t idClient);

    void run() override;
    void forceEnd();

private:
    std::vector<PlayerData> assignSkins(int numberSkins);
    void setEndOfMatch(PlayerID_t winner);
    void checkNumberPlayers();
    void broadcastMatchMssg(const std::shared_ptr<MessageSender>& message);
};

#endif
