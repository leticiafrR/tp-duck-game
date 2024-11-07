#include "client.h"

#include <string>
#include <utility>

#include "common/socket.h"

Client::Client(const std::string& hostname, const std::string& srvname, Queue<DataRecieve>& upd,
               Queue<Command>& com, DataMatch& match, const std::string& nickname):
        protocol(std::move(Socket(hostname.c_str(), srvname.c_str()))),
        updates(upd),
        commands(com),
        actualMatch(match),
        recv(protocol, updates),
        send(protocol, commands, nickname) {
    recv.start();
    send.start();
}
void Client::shutdown() {
    recv.stop();
    send.stop();
}

void Client::updateMatchChanges() {
    DataRecieve msg = updates.pop();

    switch (msg.WhatTypeIs()) {
        case MATCH_START:
            // actualMatch.up
            break;
        case GAME_START: {
            DataScene& gameScene = dynamic_cast<DataScene&>(msg);
            actualMatch.RestartGame(gameScene.scene);
            break;
        }

        case GAME_RECOUNT: {
            DataGameRecount& gameRecount = dynamic_cast<DataGameRecount&>(msg);
            if (!WasClientFinished(gameRecount.recount.matchEnded)) {}
            actualMatch.SetRecount(gameRecount.recount);
            break;
        }

        case WINNER: {
            DataWinner& winner = dynamic_cast<DataWinner&>(msg);
            actualMatch.SettWinner(winner.ID);
        }

            // case SNAPSHOT_DATA:

            // if (!WasClientFinished(msg.gameEnded)) {
            // DataSnapshot& dataSnapshot = dynamic_cast<DataSnapshot&>(msg);
            // actualMatch.UpdateGame(msg.snapshot);
            //}
            // break;
        default:
            break;
    }
}

bool Client::WasClientFinished(const bool& gameEnded) {
    if (gameEnded) {
        stop();
        return true;
    }
    return false;
}
void Client::run() {
    try {
        recv.join();
        send.join();
        // Actualizo Match
        while (_keep_running) {
            updateMatchChanges();
        }
    } catch (ConnectionFailed& e) {
        stop();
    }
    shutdown();
}
