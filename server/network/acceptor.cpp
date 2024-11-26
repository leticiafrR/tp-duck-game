#include "acceptor.h"

#include <memory>

#define FIRST_PLAYER_ID 1
#define PRINT_NEW_CONNECTION(connectionID) \
    std::cout << "New user ID: " << (connectionID) << "!" << std::endl;

AcceptorThread::AcceptorThread(const char* servname, Config& config):
        skt(servname), matchesMonitor(config) {}

void AcceptorThread::run() {
    try {
        acceptLoop();
    } catch (const LibError& e) {
    } catch (const std::exception& e) {
        std::cerr << "Exception in the Aceptor thread: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "There was an unexpected exception at the Aceptor thread.\n";
    }
    matchesMonitor.forceEndAllMatches();
    matchesMonitor.reapEndedMatches();
    killClients();
    for (auto& client: clients) {
        client->join();
    }
}

void AcceptorThread::acceptLoop() {
    uint16_t connectionId = FIRST_PLAYER_ID;
    while (_keep_running) {
        Socket peer = skt.accept();
        PRINT_NEW_CONNECTION(connectionId);
        clients.emplace_back(std::make_unique<SenderThread>(
                std::move(peer), std::ref(matchesMonitor), connectionId));
        clients.back()->start();

        reapDeadClients();
        matchesMonitor.reapEndedMatches();
        connectionId++;
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

void AcceptorThread::killClients() {
    for (auto& client: clients) {
        client->kill();
    }
}

void AcceptorThread::forceClosure() {
    skt.shutdown(2);
    skt.close();
}
