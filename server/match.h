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

#include "handlerGames.h"

#define MAX_COMMANDS 500
#define MAX_COMMANDS_PER_LOOP 100


class Match: public Thread {
private:
    // when this quantity is reached the match is started
    const int numberPlayers;

    Queue<Command> commandQueue;

    SafeMap<PlayerID_t, PlayerInfo> players;

    Config& config;

    std::mutex m;

public:
    /* has to be instanced making sure the numberPlayers is smaller than MAX_PLAYERS defined in
     * Config*/
    explicit Match(Config& config, int numberPlayers);

    /* returns a boolean indicating if the client was succesfully added. If the Match has
     * already started the method will return false, else (success) the method will include in the
     * list of Queues where the match does the broadcast the queueMesg recieved, also it will start
     * the Match thread when the `currentPlayers`reachs the quatity `cantPlayers`
     */
    bool logInPlayer(PlayerID_t idClient, const PlayerInfo& playerInfo);

    /* Executes a blocking push over the command queue (the validation over if the client is alive
     * in the current round must be done inside the  Game)*/
    /* Method called by multiple recieverThreads so it uses a queue thread safe*/
    void pushCommand(const Command& cmmd);

    /* This method takes out of the container with the players to broadcast the queue of the client
     * with the ID received. It means that it is called when the client in the middle of the match
     * has disconected (the sender thread reconizes that the client has disconnected and
     * calles this method-> CONCURRENT ACCESS) */

    /* SnapShoots to the disconnected client and also it should take off the player of the WorldMap
     * (if hasnt end) (write)*/
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
