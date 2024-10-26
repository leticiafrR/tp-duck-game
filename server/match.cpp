#include "match.h"

Match::Match(PlayerID_t idClientCreator, unsigned int numberPlayers):
        idClientCreator(idClientCreator),
        currentPlayers(0),
        numberPlayers(numberPlayers),
        commandQueue(MAX_COMMANDS),
        playersToBroadcast(numberPlayers) {}

/* method that will be called from the different Receivers threads. Has to be thread safe */
bool Match::loggInPlayer(PlayerID_t idClient, Queue<SnapShoot>* queueMsg) {
    if (!playersToBroadcast.tryInsert(idClient, queueMsg)) {
        /* If we couldnt add the queue to the map then it means that the full cpaacity of players
         * has been reached.*/
        return false;
    }
    /* Here we are efectivly adding a player to the match: increase the currentPlayers, and also if
     * this number is */
    currentPlayers++;
    /* Here we have a critical section: we want to make the checking and start the match
     * atomically*/
    std::unique_lock<std::mutex> lock(m);
    if (currentPlayers == numberPlayers && !_is_alive) {
        this->start();
    }
    return true;
}

/* method that will be called from the different Receivers threads. Has to be thread safe.
 * OJO PARA RECORDARLE A LETICIA  SI YO LO IMPLEMENTO:
 * Mètodos de lectura y escritura sobre los participantes del modelo de game/ronda (solo son ids a
 * priori) deben ser thread safe, por ejemplo el mètodo de preguntar si un cliente esta vivo debe
 * fijarse si es que el jugador esta en el juego (no estarìa si perdiò o nunca formò parte) de algun
 * contanier thread safe porque el metodo GameWorld::playerQuiting(id) editarìa el mismo contanier y
 * tambien es llamado concurrentemente
 */
bool Match::pushCommand(PlayerID_t idClient, const Command& cmmd) {
    // // the client is not able to affect the state of the current game/round
    // if (!game.PlayerAlive(idClient)) {
    //     return false;
    // }
    commandQueue.push(cmmd);
    return true;
}

// void Match::loggOutPlayer(size_t idClient) {
//     if (map_jugadores.find(id_jugador) != map_jugadores.end()) {
//         map_jugadores.erase(id_jugador);
//         logica_partida.abandonar_partida(id_jugador);
//     }

//     if (map_jugadores.empty()) {
//         return true;
//     }
//     return false;
//     queuesMsg.removeQueueMsg(idClient);
//     numberPlayers--;
// }

Queue<Command>& Match::getCommandQueue() { return commandQueue; }
