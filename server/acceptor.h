#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <list>
#include <utility>

#include "../common/common_socket.h"
#include "../common/common_thread.h"
#include "../common_queue.h"

#include "receiver.h"
// inlcude monitor

class Acceptor_thread: public Thread {
private:
    Socket skt;
    std::list<Receiver_thread*> clients;

    void accept_loop();
    // void kill_all();
    // void reap_dead();
public:
    explicit Acceptor_thread(Socket skt);
    void run() override;

    // not copyable
    Acceptor_thread(const Acceptor_thread&) = delete;
    Acceptor_thread& operator=(const Acceptor_thread&) = delete;

    // not movable
    Acceptor_thread(Acceptor_thread&&) = delete;
    Acceptor_thread& operator=(Acceptor_thread&&) = delete;
};

#endif
