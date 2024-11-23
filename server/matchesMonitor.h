#ifndef MATCHES_MONITOR_
#define MATCHES_MONITOR_

#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

#include "match.h"

struct DataMatch;

class MatchesMonitor {
private:
    std::mutex m;
    std::unordered_map<uint16_t, std::unique_ptr<Match>> matches;
    const Config& config;

public:
    explicit MatchesMonitor(const Config&);

    std::vector<DataMatch> getAvailableMatches();

    std::shared_ptr<Queue<Command>> tryJoinMatch(uint16_t matchID,
                                                 Queue<std::shared_ptr<MessageSender>>* clientQueue,
                                                 const ClientInfo& clientInfo, uint8_t& eCode);

    bool tryStartMatch(uint16_t matchID);

    void logOutClient(uint16_t matchID, uint16_t clientID);

    void reapEndedMatches();

    void forceEndAllMatches();

    void forceEndMatch(uint16_t matchID);

    // not copyable
    MatchesMonitor(const MatchesMonitor&) = delete;
    MatchesMonitor& operator=(const MatchesMonitor&) = delete;
};
#endif
