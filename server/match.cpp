#include "match.h"

Match::Match(PlayerID_t idClientCreator, unsigned int numberPlayers):
        idClientCreator(idClientCreator),
        currentPlayers(0),
        numberPlayers(numberPlayers),
        commandQueue(MAX_COMMANDS),
        players(numberPlayers) {}

/* method that will be called from the different Receivers threads. Has to be thread safe */
/* ACCESO CONCURRENTE AL RECURSO: MATCH (en especifico a los atributos)-> creo que esto metodo
 * deberìa ser protegido por otra entidad*/
bool Match::loggInPlayer(PlayerID_t idClient, const PlayerInfo& playerInfo) {
    if (!players.tryInsert(idClient, playerInfo)) {
        return false;
    }
    currentPlayers++;
    if (currentPlayers == numberPlayers && !_is_alive) {
        this->start();
    }
    return true;
}

/* method that will be called from the different Receivers threads. Has to be thread safe.*/
/* ACCESO CONCURRENTE AL RECUSURSO: MODELO DE LA PARTIDA (este mètodo deberìa ser protegido por la
 * misma match)*/
bool Match::pushCommand(PlayerID_t idClient, const Command& cmmd) {

    std::unique_lock<std::mutex> lock(mutexModel);
    if (!game.isPlayerAlive(idClient)) {
        return false;
    }
    commandQueue.push(cmmd);
    return true;
}

/*Method that wpuld be called concurrently (by the senderThreads) ante la desconexiòn de un jugador
 */
/* ACCESO CONCURRENTE AL RECURSO: MODELO DE LA PARTIDA */
void Match::loggOutPlayer(PlayerID_t idClient) {
    std::unique_lock<std::mutex> lock(mutexModel);
    if (players.tryErase(idClient)) {
        game.quitPlayer(idClient);
        currentPlayers--;
    }
}

void Match::run() {
    /*Se iniciò el thread porque ya se tiene la cantidad de juagdores -> inciializo los players en
     * a la partida (estos podrìan ir variando y entre cada ronda se debe volver a setear)*/
    game.setPlayers(players.getKeys());

    /* seguimos ejecutando en tanto no haya querido detener a la partida por un cierre forzado y por
     * lo pronto en tanto no hay un ganador de esta unica ronda.*/
    while (_keep_running && !game.hasEnded()) {
        Command cmmd;
        for (int i = 0; i < MAX_COMMANDS_PER_LOOP; i++) {
            if (commandQueue.try_pop(std::ref(cmmd))) {
                game.ejecutar(cmmd);
            } else {
                break;
            }
        }
        game.update();
        broadcast(game.getSnapshoot());
    }
}

void Match::broadcast(SnapShoot snapshoot) {
    players.applyToValues(
            [&snapshoot](PlayerInfo& player) { player.senderQueue->try_push(snapshoot); });
}
