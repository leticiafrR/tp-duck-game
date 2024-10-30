#include "match.h"

Match::Match(PlayerID_t idClientCreator, unsigned int numberPlayers):
        idClientCreator(idClientCreator),
        currentPlayers(0),
        numberPlayers(numberPlayers),
        commandQueue(MAX_COMMANDS),
        players(numberPlayers) {
    // hacer random de los 5 mapas
}

/* method that will be called from the different Receivers threads. Has to be thread safe */
/* CONCURRENT ACCESS TO THE RESOURCE: MATCH (specifically to the attributes) -> I think this method
 *should be protected by another entity a monitor of matches*/
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

void Match::pushCommand(PlayerID_t idClient, const Command& cmmd) { commandQueue.push(cmmd); }

/*Method that wpuld be called concurrently (by the senderThreads) ante la desconexiòn de un jugador
 */
/*Quito acceso concurrente al modeloencolando el evento de salir de la partida para ser procesado
 * secuencialmente */
void Match::loggOutPlayer(PlayerID_t idClient) {
    if (players.tryErase(idClient)) {
        Command quit;
        quit.playerID = idClient;
        /* Falta configurar un commandID para este comando */
        commandQueue.push(quit);
        currentPlayers--;
    }
}


void Match::run() {
    /*Se iniciò el thread porque ya se tiene la cantidad de juagdores -> inciializo los players en
     * a la partida (estos podrìan ir variando y entre cada ronda se debe volver a setear)*/
    game.setPlayers(players.getKeys());
    // hacer el s
    // enviar la informacion de los 5 mapas, asignaciòn de las skins.


    /* seguimos ejecutando en tanto no haya querido detener a la partida por un cierre forzado y por
     * lo pronto en tanto no hay un ganador de esta unica ronda.*/
    while (_keep_running && !game.hasEnded()) {
        Command cmmd;

        int countCommands = 0;
        while (countCommands < MAX_COMMANDS_PER_LOOP && commandQueue.try_pop(std::ref(cmmd))) {
            game.handleCommand(cmmd);
            countCommands++;
        }
        game.update();
        broadcast(game.getSnapshoot());
    }
}

void Match::broadcast(SnapShoot snapshoot) {
    players.applyToValues(
            [&snapshoot](PlayerInfo& player) { player.senderQueue->try_push(snapshoot); });
}
