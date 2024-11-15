#ifndef MATCHES_MONITOR_
#define MATCHES_MONITOR_

#include <unordered_map>

#include "match.h"

class MatchesMonitor {
private:
    // This should have access to the quantity of players in the match. Also im thinking about
    // taking out of the match the resposability of starting it self
    std::unordered_map<PlayerID_t, Match*> availableMatches;
    std::unordered_map<PlayerID_t, Match*> matchesOncourse;

public:
    explicit MatchesMonitor(Config);
    bool tryJoinMatch();
};


#endif
// std::unique_lock<std::mutex> lock(m);
