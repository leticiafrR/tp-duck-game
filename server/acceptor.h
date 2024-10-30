#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <list>
#include <utility>

#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"

#include "match.h"
#include "receiver.h"

class AcceptorThread: public Thread {
private:
    Socket skt;
    std::list<ReceiverThread*> clients;
    Match match;

    void acceptLoop();
    void reapDead();

    /* Only iterates through the clients and ask all of the Receiver threads to Kill themself (not
     * joining), it is ending therir executions by closing its protocols and etc (not bloquing) */
    /* To accurately end the exceution of the communication threads the Thread producer
     * (matchThread) must stop producing Snapshoos, which means that before joining alll the threads
     * of the clients the mathcThread must be stoped, otherwhise the joing of some communication
     * thread will be blocking */
    void killAllClients();

    /* Method that calls .join on each client in the container clients and frees the dynamic memory
     * used to allocate the thread. Obviously the method `killAllClients` must have been called */
    void cleanUpClientsResources();

public:
    explicit AcceptorThread(const char* servname);
    void run() override;

    /* Method called by the main thread, executes the shutdoown and closes the acepctor socket, and
     * also I BELIEVE  IT should stop the exceution of the gameLoop Thread by: closing its queue */

    /* This actions will cause the aceptor thread to get out of its loop of accepting, and then
     * there it will be managed: killing the matchThread (it means ending its execution by closing
     * its commandQueue) killing all the clients (stop the loops of sending/receiving) and . Once
     * donde this the only thing left is
     * joining all the receiver threads and also joining the match thread*/
    void forceClosure();

    // not copyable
    AcceptorThread(const AcceptorThread&) = delete;
    AcceptorThread& operator=(const AcceptorThread&) = delete;

    // not movable
    AcceptorThread(AcceptorThread&&) = delete;
    AcceptorThread& operator=(AcceptorThread&&) = delete;
};

#endif
