#include "receiver.h"

#include "data/groundDta.h"

Receiver::Receiver(ClientProtocol& prot, Queue<DataRecieve>& upd):
        protocol(prot), updates(upd), inGame(false) {}

void Receiver::run() {
    MatchStartDto matchStart = protocol.receiveMachStartDto();
    DataMatchStart match(matchStart);
    updates.push(match);
    // puede haber un try catch, por el momento no hay razon
    while (_keep_running) {
        if (!inGame) {
            GameSceneDto scene = protocol.receiveGameSceneDto();
            DataScene game(scene);
            updates.push(game);
            inGame = true;
        }
        // Snapshot snapshot = protocol.receiveGameUpdateDto();
        // updates.push(msg);
        /*if(snapshot.gameEnded){
        inGame = false;
        GameRecountDto recount = protocol.receiveGameRecountDto();
        DataGameRecount count(recount);
        updates.push(count);
        }*/
    }

    PlayerID_t win = protocol.receiveMatchWinner();
    DataWinner winner(win);
    updates.push(winner);
}
