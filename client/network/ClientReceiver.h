#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>

#include "../../data/dataTransferObjects.h"
#include "../../data/gameScene.h"
#include "common/thread.h"

#include "ClientProtocol.h"

class ClientReceiver: public Thread {
private:
    ClientProtocol& protocol;  // le pertenece al client
    MatchStartDto infoMatch;
    GameSceneDto infoRound;  // updated 5 times
    // std::string username;

public:
    explicit ClientReceiver(ClientProtocol& protocol): protocol(protocol) {}
    bool FindMatch() {
        protocol.sendNickname("Messi");
        return protocol.receiveStateOfJoining();
    }

    void RoundLoop() { infoRound = protocol.receiveGameSceneDto(); }

    void run() override {
        if (FindMatch()) {
            infoMatch = protocol.receiveMachStartDto();
            RoundLoop();
        }
    }
    void Saludar() { std::cout << "[CLIENTE RECEIVER]: Hola\n"; }
};


/**
 * se encarga de primero enviar el nombre del jugador
 * recibe bool de si se logrò unir
 * lanza al sender para enviar codes
 * 1) recibe data inicial de la partida (matchStartDto, este tiene los jugadores)
 *      5) recibe data inicial del juego (gameSceneDto)
 *
 *              recibe solo snapshots
 * hasta que uno de los snapshots diga que se termina el dato y vuelve a iniciar otro game
 *
 */
// class ReceiverThread: public Thread {
// private:
//     ClientPro
// public:
//     explicit ReceiverThread();

//     void run() override;
//     void kill();

//     //~ReceiverThread() override;
// };


#endif
