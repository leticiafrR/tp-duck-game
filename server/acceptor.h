#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <list>
#include <utility>

#include "sender.h"

class AcceptorThread: public Thread {
private:
    Socket skt;
    std::list<SenderThread*> clients;
    Match match;

    void acceptLoop();
    void reapDead();

    /* This method first kills the clients (that havent joined a match), then it forces the end of
     * the unique match available and this will make sure to kill the communication threads of its
     * participants. Once donde this thw only thing left if joining the threads ofall the clients
     * and also the match*/
    void killAllClients();

    /* Method that calls .join on the clients threads and also on the match thread */
    void cleanUpThreads();

public:
    explicit AcceptorThread(const char* servname, Config& config);
    void run() override;

    /* This actions will cause the aceptor thread to get out of its loop of accepting, and then
     * there it will be managed: killing the matchThread (that will also kill its players)*/
    void forceClosure();

    ~AcceptorThread();

    // not copyable
    AcceptorThread(const AcceptorThread&) = delete;
    AcceptorThread& operator=(const AcceptorThread&) = delete;

    // not movable
    AcceptorThread(AcceptorThread&&) = delete;
    AcceptorThread& operator=(AcceptorThread&&) = delete;
};

#endif
