#include "match.h"

Match::Match(size_t idClientCreator): idClientCreator(idClientCreator), numberPlayers(0) {}

void Match::addClient(size_t idClient, Queue<Message>* queueMsg) {
    queuesMsg.addQueueMsg(idClient, queueMsg);
    numberPlayers++;
}

void Match::removeClient(size_t idClient) {
    queuesMsg.removeQueueMsg(idClient);
    numberPlayers--;
}

Queue<Command>& Match::getCommandQueue(){
    return commandQueue;
}
