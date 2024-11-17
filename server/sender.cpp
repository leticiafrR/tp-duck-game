#include "sender.h"


SenderThread::SenderThread(Socket&& sktPeer, Match& match, PlayerID_t idClient):
        match(match), senderQueue(MAX_MESSAGES), protocol(std::move(sktPeer)), idClient(idClient) {}

bool SenderThread::joinedAMatch() { return _joinedAMatch; }

void SenderThread::run() {
    try {
        std::string nickname = protocol.receiveNickName();
        PlayerInfo info;
        info.nickName = nickname;
        info.senderQueue = &senderQueue;
        if (!match.logInPlayer(idClient, info)) {
            protocol.sendResultOfJoining(false);
        } else {
            _joinedAMatch = true;
            std::cout << "entra\n";
            sendLoop();
        }
    } catch (const ConnectionFailed& c) {
        // conexion failed even before the player has joined a match
    } catch (const LibError& e) {

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "ERROR: An unkown error was catched at the receiveLoop of the client with ID :"
                  << idClient << "\n";
    }
    _joinedAMatch = false;
    std::cout << "termina seder\n";
}

void SenderThread::sendLoop() {
    ReceiverThread receiver(idClient, match, protocol);
    receiver.start();
    try {
        protocol.sendResultOfJoining(true);
        while (_keep_running) {
            auto messageSender = senderQueue.pop();
            messageSender->execute(std::ref(protocol));
        }
    } catch (const ConnectionFailed& c) {
        match.logOutPlayer(idClient);
    } catch (const ClosedQueue& q) {
        // siempre que se envia el mensaje de que terminò la partida en la que estàbamos se catchea
        // este error
        // si nos terminò la partida -> ya cerrò nuestro protocolo y todas las queues
    }
    receiver.join();
}

void SenderThread::kill() {
    if (!_joinedAMatch) {
        protocol.endConnection();
    }
}

SenderThread::~SenderThread() {
    if (_is_alive) {
        std::cout << "se llamarà a kill\n";
        kill();
        join();
    }
}
