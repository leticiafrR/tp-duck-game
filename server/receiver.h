#ifndef RECEIVER_H
#define RECEIVER_H

#include <utility>

#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"

#include "match.h"
#include "sender.h"
#include "serverProtocol.h"

// as the Reciver is working as a client manager, it has the contact with the match and also the
// client id thus we dont want the Sender to has this this mentioned would be redundant.
class ReceiverThread: public Thread {
    // lo que tendrìa que pasar es que se lance al Reciver y este de alguna forma se consigue un
    // puntero a
private:
    size_t idClient;  // cppcheck-suppress unusedStructMember
    // a priori sè que necesitamos a la partida para pedirle a la misma que saque a este jugador
    // cuando nos demos cuenta que està muerto (por diversas razones) ademàs de que en el
    // constructor esta nos proporciona la queue que necesita el hilo
    Match& match;


    // atributes necesatios solo para el funcionamiento del hilo de comunicaciòn
    ServerProtocol protocol;
    Queue<Command>& commandQueue;

    void receiveLoop();

public:
    // initializates the command queue where the reciever pushes with the command queue that the
    // match recieved gives us and also binds this client with the only one match that we have (i
    // mean its queue of messages is included to the broadcast list)
    explicit ReceiverThread(Match& match, Socket sktPeer, size_t idClient);
    void run() override;
    void forceEnd();

    ~ReceiverThread() override;
};
#endif
