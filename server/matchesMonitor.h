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
    std::unordered_map<PlayerID_t, std::unique_ptr<Match>> matches;
    const Config& config;

public:
    explicit MatchesMonitor(const Config&);

    std::vector<DataMatch> getAvailableMatches();

    std::shared_ptr<Queue<Command>> tryJoinMatch(PlayerID_t matchID, PlayerID_t player,
                                                 const PlayerInfo& playerInfo);

    // returns false if there wasnt enough payers
    bool tryStartMatch(PlayerID_t matchID);

    void logOutPlayer(PlayerID_t matchID, PlayerID_t player);

    // called everytime someone asks for availableMatches (sender) and everyTime the server accepts
    // a new conextion
    void reapEndedMatches();

    void forceEndAllMatches();

    void forceEndMatch(PlayerID_t matchID);

    // not copyable
    MatchesMonitor(const MatchesMonitor&) = delete;
    MatchesMonitor& operator=(const MatchesMonitor&) = delete;
};
#endif
