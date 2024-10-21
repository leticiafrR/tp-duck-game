#include "sender.h"


SenderThread::SenderThread(Match* myMatch, ProtocolServer& protocol, size_t idClient):
        myMatch(myMatch), protocol(protocol), idClient(idClient) {}
