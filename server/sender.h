#ifndef SENDER_H
#define SENDER_H
#include <cstddef>

#include "../common/queue.h"
#include "../common/thread.h"

#include "match.h"

class ProtocolServer;

class SenderThread: public Thread {
private:
    Match* myMatch;
    ProtocolServer& protocol;
    size_t idClient;

public:
    explicit SenderThread(Match* myMatch, ProtocolServer& protocol, size_t idClient);
};

#endif
