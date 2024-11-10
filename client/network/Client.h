#ifndef CLIENT_H
#define CLIENT_H
// #include "../../data/command.h"
// #include "../../data/snapshot.h"
#include <string>

#include "common/queue.h"
#include "common/thread.h"

#include "sender.h"

/*
envio nickname + data

*/


class Client {
private:
    ClientProtocol protocol;
    Queue<DataRecieve>& updates;
    Queue<CommandCode>& commands;
    DataMatch& actualMatch;
    Receiver* recv;
    Sender* send;
    void updateMatchChanges();
    bool WasClientFinished(const bool& gameEnded);

public:
    Client(const std::string& hostname, const std::string& srvname, Queue<DataRecieve>& upd,
           Queue<Command>& com, DataMatch& match, const std::string& nickname);
};
class Client {
    Queue<CommandCode> inputQueue;
    Queue<Snapshot> outputQueue;

private:
    // envia nickname
    void MeetServer();

    // receibo un boool de si no se p

    // aceptor lanza sender y este lanza al receiver

    /* data struct PlayerData {
    PlayerID_t playerID;
    uint8_t playerSkin;
    std::string nickname;

    PlayerData(): playerID(0), playerSkin(0), nickname("") {}
    PlayerData(PlayerID_t playerID, uint8_t playerSkin, const std::string& nickname):
            playerID(playerID), playerSkin(playerSkin), nickname(nickname) {}
};*/

public:
    /*
    1.datos jugadores (player Info)
    2.datos escenario*/


    void SendCommand(const CommandCode& code);
    Snapshot ReceiveUpdate();
    Client(/* args */);
    ~Client();
};


#endif
