#include "lobby.h"

// estructura principal del lobby (run)

// -El ciclo para recibir comandos de lobby y los respuestas-> se sale porque creo una match o
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


// (getAvailableMatches() metodo protegido del monitor -> acceso de lectura a los status de las
// matches
// -> debe ser mutuamente excluyente con waitingForMatchStarting-> acceso de escritura al status de
// la match (si es el player creador)

// crear una partida nueva -> acceso de escritura al container con
// cambio de available a on course -> acceso de escritur
