#include "acceptor.h"

#define PRINT_NEW_CONNECTION() std::cout << "New user connected!" << std::endl;
#define TEST_NUMBER_PLAYERS_IN_MATCH 2

AcceptorThread::AcceptorThread(const char* servname, Config& config):
        skt(servname), match(config, TEST_NUMBER_PLAYERS_IN_MATCH) {}

void AcceptorThread::forceClosure() {
    skt.shutdown(2);
    skt.close();
}
void AcceptorThread::killAllClients() {
    // first we kill the ones that arent part of a match
    for (auto& client: clients) {
        client->kill();
    }
}
void AcceptorThread::run() {
    try {
        acceptLoop();
    } catch (const LibError& e) {
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "ACEPTOR: el hilo saliò de su loop-> ahora estamos matando a la partida\n";
    /* Forcing the end of the match that will kill all of its clients  */
    match.forceEnd();
    cleanUpThreads();
}

/* Method that will fail (throw an execption) when the main thread ask the acceptor to forceClosure
 */
void AcceptorThread::acceptLoop() {
    PlayerID_t idClient = 1;

    while (_keep_running) {
        Socket peer = skt.accept();

        PRINT_NEW_CONNECTION();

        SenderThread* client = new SenderThread(std::move(peer), std::ref(match), idClient);
        clients.push_back(client);
        client->start();
        reapDead();
        idClient++;
    }
}

void AcceptorThread::reapDead() {
    clients.remove_if([](SenderThread* client) {
        if (!client->is_alive()) {
            client->join();
            delete client;
            return true;
        }
        return false;
    });
}


void AcceptorThread::cleanUpThreads() {
    match.join();
    for (auto& client: clients) {
        client->join();
        delete client;
    }
    clients.clear();
}
