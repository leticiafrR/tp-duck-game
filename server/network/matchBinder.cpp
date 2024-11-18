#include "matchBinder.h"

#include <memory>

const bool FAIL_JOINING = false;
const bool SUCCESS_JOINING = true;
const PlayerID_t REFRESH = 0;

// estructura principal del MatchBinder (run)

// -El ciclo para recibir comandos de MatchBinder y los respuestas-> se sale porque creo una match o
// porque se uniò a una -saliendo del bucle se usa el monitor de partidas para loggIn al client a la
// partida
//- si es que decidiò crear una partida:
//      - se recibe por el protocolo el comando para iniciar la partida
//      - se pushea a la queue que devuelve loggin (de la match)
//      - se ejecuta monitor.waitForMatchStarting(ID_player, ID_Match) {
//           std::unique_lock(m); -> mutex para el acceso a las available matches
//          -match.waitForMatchStarting(ID_player)
//          - if(ID_Player== ID_match){
//              this->transferStaredMatch();
//            }
//        }
//
//-si es que solo se uniò a una partida:
//      - se ejecuta de frente waitForMatchStarting


MatchBinder::MatchBinder(MatchesMonitor& _monitor, bool _joinedAMatch, const PlayerID_t& _id,
                         Queue<std::shared_ptr<MessageSender>> _senderQueue,
                         ServerProtocol& _protocol, std::shared_ptr<Queue<Command>>& _matchQueue):
        monitor(_monitor),
        playerID(_id),
        senderQueue(_senderQueue),
        protocol(_protocol),
        _joinedAMatch(_joinedAMatch),
        matchQueue(_matchQueue) {}

void MatchBinder::waitingStartMatch() {
    bool start = false;
    while (!start) {
        start = protocol.receiveStartMatch();
    }
    monitor.StartAMatch(playerID);
}

void MatchBinder::bind() {
    try {
        PlayerID_t matchID;
        while (!_joinedAMatch) {
            protocol.sendActivesMatches(monitor.getAvailableMatches());
            matchID = protocol.receiveTryJoinMatch();
            if (matchID != REFRESH) {
                std::shared_ptr<Queue<Command>> commandQueue = monitor.tryJoinMatch(matchID);
                if (commandQueue != nullptr) {
                    protocol.sendResultOfJoining(SUCCESS_JOINING);
                    if (matchID == playerID) {
                        waitingStartMatch();
                    }
                    _joinedAMatch = true;
                } else {
                    protocol.sendResultOfJoining(FAIL_JOINING);
                }
            }
        }

    } catch (const ClosedQueue& cqe) {

    } catch (const BrokenProtocol& bpe) {}
}
