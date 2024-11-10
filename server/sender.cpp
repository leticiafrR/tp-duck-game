#include "sender.h"


SenderThread::SenderThread(Socket&& sktPeer, Match& match, PlayerID_t idClient):
        match(match), senderQueue(MAX_MESSAGES), protocol(std::move(sktPeer)), idClient(idClient) {}

bool SenderThread::joinedAMatch() { return _joinedAMatch; }

void SenderThread::run() {
    try {
        std::string nickname = protocol.receiveNickName();

        std::cout << "\nSENDER OF CLIENT:" << idClient << " with Nickname " << nickname << "\n";

        PlayerInfo info;
        info.nickName = nickname;
        info.senderQueue = &senderQueue;

        if (!match.logInPlayer(idClient, info)) {
            std::cout << "\nSENDER OF CLIENT: looks like the match didnt let us join!!...\n "
                         "...Sending false to the client\n ";
            protocol.sendResultOfJoining(false);
        } else {
            std::cout << "\nSENDER[" << idClient << "]:Client joined the match! \n ";
            _joinedAMatch = true;
            // CLIENT THAT IS PART OF A MATCH!
            sendLoop();
        }
    } catch (const ConnectionFailed& c) {
        // conexion failed even before the player has joined a match
        protocol.endConnection();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "ERROR: An unkown error was catched at the receiveLoop of the client with ID :"
                  << idClient << "\n";
    }
}

// got here once the client is really loged in into a match
void SenderThread::sendLoop() {
    std::cout << "\nSENDER[" << idClient << "]: entering to the send loop.\n\n";
    ReceiverThread receiver(idClient, match, protocol);
    receiver.start();

    try {
        protocol.sendResultOfJoining(true);
        std::cout << "\nSENDER[" << idClient << "]: Enviamos: couldJoinMatch = True\n";

        while (_keep_running) {
            auto message = senderQueue.pop();
            std::cout << "SENDER[" << idClient << "]: Enviamos:" << message->descriptionCont()
                      << " \n";
            message->execute(std::ref(protocol));
        }
    } catch (const ConnectionFailed& c) {
        match.logOutPlayer(idClient);
        protocol.endConnection();  // this will make the receiver fail (if it hasnt yet)
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
    try {
        if (_is_alive) {
            kill();
            join();
        }
    } catch (...) {
        std::cout << "ERROR: se atrapò un error en el destructor  del sender\n";
    }
}
