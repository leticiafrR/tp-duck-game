#include "acceptor.h"

#include <memory>

#define FIRST_PLAYER_ID 1
#define PRINT_NEW_CONNECTION() std::cout << "New user connected!" << std::endl;

AcceptorThread::AcceptorThread(const char* servname, Config& config):
        skt(servname), matchesMonitor(config) {}

void AcceptorThread::run() {
    try {
        acceptLoop();
    } catch (const LibError& e) {

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "There was an unexpected exception at the Aceptor thread.\n";
    }
    // std::cout <<"antes de matar a todas las partidas\n";
    matchesMonitor.forceEndAllMatches();
    // std::cout << "Se mataron a todas las partidas\n";
    std::cout << "\nantes de recoger a las ended matches\n";
    matchesMonitor.reapEndedMatches();
    std::cout << "Se recogieron a todas las ended Matches\n";
    killAllClients();
    reapDeadClients();
}

void AcceptorThread::acceptLoop() {
    PlayerID_t idClient = FIRST_PLAYER_ID;

    while (_keep_running) {
        Socket peer = skt.accept();
        PRINT_NEW_CONNECTION();
        clients.emplace_back(std::make_unique<SenderThread>(std::move(peer),
                                                            std::ref(matchesMonitor), idClient));
        clients.back()->start();

        reapDeadClients();
        matchesMonitor.reapEndedMatches();
        idClient++;
    }
}

void AcceptorThread::reapDeadClients() {
    clients.remove_if([](std::unique_ptr<SenderThread>& client) {
        if (!client->is_alive()) {
            client->join();
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

void AcceptorThread::forceClosure() {
    skt.shutdown(2);
    std::cout << "Despuès de hacer el shutdown\n";
    skt.close();
}
