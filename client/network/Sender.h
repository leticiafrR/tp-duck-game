#ifndef SENDER_H
#define SENDER_H
#include "common/queue.h"
#include "common/thread.h"

#include "ClientProtocol.h"

class Sender: public Thread {
private:
    ClientProtocol& protocol;
    Queue<CommandCode>& cmmdQueue;

public:
    Sender(ClientProtocol& protocol, Queue<CommandCode>& cmmdQueue):
            protocol(protocol), cmmdQueue(cmmdQueue) {}

    void run() override {
        std::cout << "el sender esta corriendo\n";
        try {
            while (_keep_running) {
                CommandCode cmmd = cmmdQueue.pop();
                protocol.sendCommand(cmmd);
            }
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        } catch (...) {
            std::cerr << "ERROR: An unkown error was catched at sending a message from the server"
                      << std::endl;
        }
    }
    void kill() {
        // espera a que se envie el ultimo mensaje
        cmmdQueue.close();
        // recien cuando se cierre la cola se puede hacer join
    }
};


#endif
