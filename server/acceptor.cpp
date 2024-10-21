#include "acceptor.h"

Acceptor_thread::Acceptor_thread(Socket skt, Queue<Command>& q_commands):
        skt(std::move(skt)), speakers(), q_commands(q_commands), id_match_generator(0) {}


void Acceptor_thread::run() {
    try {
        accept_loop();
    } catch (const LibError& e) {

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    //    kill_all();
}

void Acceptor_thread::accept_loop() {
    size_t id_client = 0;
    while (_keep_running) {

        Socket peer = skt.accept();
        Receiver_thread* client =
                new Receiver_thread(q_commands, std::move(peer), id_client, speakers);
        clients.push_back(client);
        client->start();
        reap_dead();
        id_client++;
    }
}
