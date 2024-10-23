#include "acceptor.h"

AcceptorThread::AcceptorThread(const char* servname): skt(servname) {}


void AcceptorThread::run() {
    try {
        acceptLoop();
    } catch (const LibError& e) {

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    // killAll();
}

void AcceptorThread::acceptLoop() {
    size_t idClient = 1;
    while (_keep_running) {
        Socket peer = skt.accept();
        //with a single match we already know the queue of commands where the receiver pushes, 
        //but also the client needs to know the match so when it realizes it has disconected it aks to the match to loggOut it self
        ReceiverThread* client = new ReceiverThread(match, std::move(peer), idClient);
        clients.push_back(client);
        client->start();
        reapDead();
        idClient++;
    }
}

void AcceptorThread::reapDead() {
    clients.remove_if([](ReceiverThread* client) {
        if (!client->is_alive()) {
            client->join();
            delete client;
            return true;
        }
        return false;
    });
}

// void AcceptorThread::killAll() {
//     for (auto& client: clients) {
//         client->forceEnd();
//         client->join();
//         delete client;
//     }
//     clients.clear();
// }
