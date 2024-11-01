#include "acceptor.h"

#define PRINT_NEW_CONNECTION() std::cout << "New user connected!" << std::endl;
#define TEST_NUMBER_PLAYERS_IN_MATCH 1

AcceptorThread::AcceptorThread(const char* servname, Config& config):
        skt(servname), match(config, TEST_NUMBER_PLAYERS_IN_MATCH) {}


void AcceptorThread::run() {
    try {
        acceptLoop();
    } catch (const LibError& e) {

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    /* Forcing the end of the loops of the threads */
    match.stop();  // maybe sould override this method to also close its command queue
    killAllClients();

    /* cleaning the resources of the  threads*/
    match.join();
    cleanUpClientsResources();
}

void AcceptorThread::forceClosure() {
    skt.shutdown(1);
    skt.close();
}

/* Method that will fail (throw an execption) when the main thread ask the acceptor to forceClosure
 */
void AcceptorThread::acceptLoop() {
    PlayerID_t idClient = 1;
    while (_keep_running) {
        Socket peer = skt.accept();

        PRINT_NEW_CONNECTION();

        ReceiverThread* client = new ReceiverThread(std::ref(match), std::move(peer), idClient);
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

void AcceptorThread::killAllClients() {
    for (auto& client: clients) {
        client->kill();
    }
}

void AcceptorThread::cleanUpClientsResources() {
    for (auto& client: clients) {
        client->join();
        delete client;
    }
    clients.clear();
}
