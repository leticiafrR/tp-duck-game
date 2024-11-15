#include "sender.h"

// pregunta, si es que un jugador puede pasar un tiempo ilimitado en un lobby, còmo se mata al
// cliente? -> cerrando su protocolo
SenderThread::SenderThread(Socket&& sktPeer, MatchesMonitor& matches, PlayerID_t idClient):
        matches(matches),
        senderQueue(MAX_MESSAGES),
        protocol(std::move(sktPeer)),
        idClient(idClient) {}

bool SenderThread::joinedAMatch() { return _joinedAMatch; }

void SenderThread::run() {
    // std::shared_ptr<Queue<Command>> matchQueue;

    // Lobby(matchesMonitor, std::ref(_joinedAMatch), IDPlayer, std::ref(senderQueue), protocol,
    // matchQueue); lobby.start() Looby.join()

    /*  Del lobby se debe salir teniendo:
        -   Si el booleano _joinedAMatch correctamente seteado

        -   (en caso de que se desconectò el cliente y no es cogiò una match): solo se debe
       cerciorar que el booleano _joinedAMAtch sea false y que se haga protocol.endConection().

        -   (en caso de que no se haya desconectado el cliente antes de poder incluirlo en alguna
       partida) se terminò el hilo solo porque el cliente YA SE INCLUYÒ EFECTIVAMENTE EN UNA MATCH,
       no importa si de fondo el Lobby haya tenido que pedirle al monitor de matches que cree una
       partida o si solo uniò al jugador a unaya existente, etc.

            -> ¿Què implica que se haya unido al jugador a una partida?
                - que se accediò a esa match y se le pidiò logInPlayer, haciendo que se incluya en
       el SafeMap con las queues a las que se les hace broadcast la cola del cliente.
                - Que el puntero que se le enviò al lobby (matchQueue) apunte a la queue de la match
       (el mètodo `std::shared_ptr<Queue<Command>> Match::logInPlayer(...)` devuelve este puntero.

                ( OJO: Este tendrìa que ser accedido a travès del matchesMonitor, hace falta agregar
       este mètodo, al monitor teniendo en cuenta la protecciòn por el acceso concurrente, la
       verificaciòn de la cantidad de jugadores faltantes en la partida ya que ese mètodo de la
       match lanza excepciòn si se trata de unir a un jugador a una partida que ya no le faltaban
       jugadores (que ha de haber sido disparada por el mismo monitor de matches cuando se estaba
       agregando al ultimo jugador que llenò la match. Para lo mencionado, la match le proporciona
       al monitor Matches el mètodo `int Match::missingPlayers()` )

                - El lobby tiene que almacenar en su estado interno el ID de la partida a la que se
       uniò el jugador y proporcionar un getter de este.

    */

    if (!_joinedAMatch) {
        return;
    }

    // ReceiverThread receiver(idClient, matchQueue , protocol);
    // receiver.start();
    // sendLoop(lobby.getMatchID());
    // receiver.join();
}

void SenderThread::sendLoop(uint32_t matchID) {
    try {
        while (_keep_running) {
            auto messageSender = senderQueue.pop();
            messageSender->execute(std::ref(protocol));
        }

    } catch (const ConnectionFailed& c) {

        // matchesMonitor.logOutPlayer(matchID, idClient);
        protocol.endConnection();

    } catch (const LibError& e) {

        // matchesMonitor.logOutPlayer(matchID, idClient);
        protocol.endConnection();

    } catch (const ClosedQueue& q) {
        // got here because the match has killed us (is the only one that closes this queue)
        // we dont have to either try to remove the Player off the match nor endTheConection
        // the messageSender->execute() that had that killer message has done it).
    } catch (...) {
        std::cout << "HUBO UN ERROR EN EL HILO SENDER!!\n";
    }
}

void SenderThread::kill() {
    if (!_joinedAMatch) {
        protocol.endConnection();
    }
}

// no es definitivo este bloque try-catch, solo era para asegurarme que no crashee el servidor
// (ya que si se lanza una excepciòn en un desructor los programas crashean)
SenderThread::~SenderThread() {
    try {
        if (_is_alive) {
            kill();
            join();
        }
    } catch (...) {
        std::cout << "ERROR: se atrapò un error en el destructor  del sender\n";
    }
}
