#ifndef MATCH_H
#define MATCH_H

#include <atomic>
#include <memory>
#include <mutex>
#include <string>

#include "../common/command.h"
#include "../common/queue.h"
#include "../common/safeMap.h"
#include "../common/snapShoot.h"
#include "../common/thread.h"
#include "../data/id.h"

#include "clientMessages.h"
#include "config.h"
#include "handlerGames.h"
#include "serverProtocol.h"

#define MAX_COMMANDS 500
#define MAX_COMMANDS_PER_LOOP 100


class Match: public Thread {
private:
    // useful to see when to start the match and also when it... has ended
    std::atomic<unsigned int> currentPlayers;
    // when this quantity is reached the match is started
    const unsigned int numberPlayers;

    Queue<Command> commandQueue;

    SafeMap<PlayerID_t, PlayerInfo> players;

    Config& config;

    std::mutex m;

public:
    /* has to be instanced making sure the numberPlayers is smaller than MAX_PLAYERS defined in
     * Config*/
    explicit Match(Config& config, unsigned int numberPlayers);

    /* returns a boolean indicating if the client was succesfully added. If the Match has
     * already started the method will return false, else (success) the method will include in the
     * list of Queues where the match does the broadcast the queueMesg recieved, also it will start
     * the Match thread when the `currentPlayers`reachs the quatity `cantPlayers`
     */
    bool loggInPlayer(PlayerID_t idClient, const PlayerInfo& playerInfo);

    /* Executes a blocking push over the command queue (the validation over if the client is alive
     * in the current round must be done inside the  Game)*/
    /* Method called by multiple recieverThreads so it uses a queue thread safe*/
    void pushCommand(PlayerID_t idClient, const Command& cmmd);

    /* This method takes out of the container with the players to broadcast the queue of the client
     * with the ID received. It means that it is called when the client in the middle of the match
     * has disconected (the sender thread reconizes that the client has disconnected and
     * calles this method-> CONCURRENT ACCESS) */

    /* SnapShoots to the disconnected client and also it should take off the player of the WorldMap
     * (if hasnt end) (write)*/
    void loggOutPlayer(PlayerID_t idClient);

    void run() override;

private:
    /* */
    void broadcastMatchMssg(const std::shared_ptr<ClientMessage>& message);
};

#endif
// Al instanciarse la partida se intancia unna game con un mapa ya predefinido

/* En el loop del match cada vez que se pide un snapshoot, justo despuès se le pregunta al gameWorld
 * si es que el juego acabò (gameIsOver) si sì acabo se envìa ese ùltimo SnapShoot a los jugadores y
 * se llama a matchThread.stop(). Si el juego no acabo se continua con el broadcast del snapshoot y
 * sigue el loop */

//================================================================================================

/* Cuando se quiere forzar la finalizaciòn de la partida (aun quedan jugadores en el modelo y en la
 * lista para hacer broadCast) */

/*      clearAllPlayer (para no hacer màs sends) (y tal vez tambièn se deberìa de
 *      cerrar la commandQueue para que los hilos receivers ya no puedan enviar
 *      cosas a la partida) */

/*      (ya no serìa necesario sacar a todos los jugadores de la lògica de la
 *      partida) pues ya no se usarà màs a la partida simplemente */

//================================================================================================

/* Cuando se terminò ya toda la partida se debe de realizar */

/*      Al GameWorld se le pide get Stadistics Of Game (para saber cuàl es el ganador)*/
/*      Se envia a la */

/*      clearAllPlayer (para no hacer màs sends) (y tal vez tambièn se deberìa de
 *      cerrar la commandQueue para que los hilos receivers ya no puedan enviar
 *      cosas a la partida) */

/*      (ya no serìa necesario sacar a todos los jugadores de la lògica de la
 *      partida) pues ya no se usarà màs a la partida simplemente */

/* Ahora, cuando se està forzando tod*/
