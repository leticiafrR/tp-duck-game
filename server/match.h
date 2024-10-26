#ifndef MATCH_H
#define MATCH_H
#include <atomic>
#include <cstdint>
#include <unordered_map>

#include "../common/queue.h"
#include "../common/safeMap.h"
#include "../common/thread.h"
// #include "/data/"-> esto es para el alias

#include "serverProtocol.h"

#define TEST_MAX_PLAYERS 1

#define MAX_COMMANDS 100

typedef uint32_t PlayerID_ty;    // esto se obtiene de la carpeta data y desaparecerà despuès
typedef struct Message Message;  // desaparece con la integraciòn del protocolo
typedef struct Command {};       // desaparece con la integraciòn del protocolo
class GameWorld;

class Match: public Thread {
private:
    PlayerID_ty idClientCreator;

    std::atomic<unsigned int> currentPlayers;
    // when this quantity is reached the match is started
    const unsigned int numberPlayers;

    Queue<Command> commandQueue;
    SafeMap<PlayerID_ty, Queue<Message>*> playersToBroadcast;
    std::mutex m;

    // GameWorld game;


public:
    explicit Match(PlayerID_ty idClientCreator = 1, unsigned int numberPlayers = TEST_MAX_PLAYERS);

    /* returns a boolean indicating if the client was succesfully added. If the Match has
     * already started the method will return false, else (success) the method will include in the
     * list of Queues where the match does the broadcast the queueMesg recieved and will set
     * the pointer Queue<Command> to point the queue from where this match process.
     * Also it will start the Match thread when the `currentPlayers`reachs the quatity `cantPlayers`
     */
    bool loggInPlayer(PlayerID_ty idClient, Queue<Message>* queueMsg);

    /* If the client who wants to push in the command queue doesnt have the permissions to affect
     * the state of the match (he/she is dead in the current game/round) it wont push nothing and
     * will only return False. In the other hand, if the client is able to push commands it will
     * execute a blocking push over the queue of commands of the match*/

    /* Method called by multiple recieverThreads, but uses a queue multithreat safe*/
    bool pushCommand(PlayerID_ty idClient, Command& cmmd);

    /* Method called whenthe sender thread reconizes that the client/player has disconnected, may be
     * called concurrently to "write" (delete) the resource: playersToBroadcast to not send messages
     * to the disconnected client and also it should take off the player of the WorldMap (write)*/
    void loggOutPlayer(PlayerID_ty idClient);

    void run() override;


    Queue<Command>& getCommandQueue();
};

#endif
