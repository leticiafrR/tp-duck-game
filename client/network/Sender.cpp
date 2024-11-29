#include "Sender.h"

#define THREAD_KILLED_FOLLOWING_OWNER                                                            \
    "Receiver thread (owner of sender) stopped (check reason why receiver was killed: could be " \
    "client app finalization or receiver detected server disconnection) anyway it has killed "   \
    "also the receiver thread."
#define THREAD_KILLED_SERVER_DISCONNECTED                                                       \
    "Communication threads to the server killed due to detecting the server disconnection (so " \
    "don't have threads starving)"

Sender::Sender(ClientProtocol& protocol, Queue<Command>& cmmdQueue):
        protocol(protocol), cmmdQueue(cmmdQueue) {}

void Sender::run() {
    try {
        while (_keep_running) {
            Command cmmd = cmmdQueue.pop();
            protocol.sendCommand(cmmd);
        }
    } catch (const ClosedQueue& q) {
        std::cerr << "[Sender Thread]: (catch closed queue) " << THREAD_KILLED_FOLLOWING_OWNER
                  << std::endl;
    } catch (const ConnectionFailed& c) {
        std::cerr << "[Sender Thread]: " << THREAD_KILLED_SERVER_DISCONNECTED << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[Sender Thread]: exception caught: " << e.what() << std::endl;
    }
}

void Sender::kill() {
    // the receiver has the responsability of end the connection
    cmmdQueue.close();
}
