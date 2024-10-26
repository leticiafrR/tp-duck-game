#include "match.h"

Match::Match(PlayerID_ty idClientCreator, unsigned int numberPlayers):
        idClientCreator(idClientCreator),
        currentPlayers(0),
        numberPlayers(numberPlayers),
        commandQueue(MAX_COMMANDS),
        playersToBroadcast(numberPlayers) {}

/* method that will be called from the different Receivers threads. Has to be thread safe*/
bool Match::loggInPlayer(PlayerID_ty idClient, Queue<Message>* queueMsg) {
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

/* method that will be called from the different Receivers threads. Has to be thread safe*/
bool Match::pushCommand(PlayerID_ty idClient, const Command& cmmd) {
    // // the client is not able to affect the state of the current game/round
    // if (!game.isAlive(idClient)) {
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
