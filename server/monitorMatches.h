#ifndef MONITOR_MATCHES_H
#define MONITOR_MATCHES_H
#include <map>

#include "match.h"

class MonitorMatches {
private:
    std::map<size_t, Match*> matches;
    std::map<size_t, Match*> notStartedMatches;
    std::mutex mtx;

public:
    void addNewMatch(Match* match, size_t idClientCreator);
    void startMatch(size_t idClientCreator);
    void joinToMatch(size_t idClientCreator, size_t idClient);
};
#endif
