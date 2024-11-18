#include "matchesMonitor.h"

#include "data/dataMatch.h"

MatchesMonitor::MatchesMonitor(const Config& config): config(config) {}

void MatchesMonitor::reapEndedMatches() {
    std::unique_lock<std::mutex> lck(m);
    for (auto it = matches.begin(); it != matches.end();) {
        if (it->second->isOver()) {
            it->second->join();
            it = matches.erase(it);
        } else {
            ++it;
        }
    }
}

std::vector<DataMatch> MatchesMonitor::getAvailableMatches() {
    reapEndedMatches();

    std::unique_lock<std::mutex> lck(m);
    std::vector<DataMatch> availableMatches;
    for (auto& pair: matches) {
        pair.second->loadDataIfAvailble(availableMatches);
    }
    return availableMatches;
}
// if doesnt exist
std::shared_ptr<Queue<Command>> MatchesMonitor::tryJoinMatch(PlayerID_t matchID,
                                                             PlayerID_t playerID,
                                                             const PlayerInfo& playerInfo) {
    std::unique_lock<std::mutex> lck(m);
    auto it = matches.find(matchID);
    if (it != matches.end()) {
        return matches[matchID]->logInPlayer(playerID, playerInfo);
    }
    if (matchID == playerID) {
        matches.emplace(matchID, std::make_unique<Match>(config, playerID));
        return matches[matchID]->logInPlayer(playerID, playerInfo);
    }
    std::cerr << "ERROR: Trying to join a match that doesnt exist, but MatchID is different from "
                 "playerID .\n";
    return nullptr;
}

bool MatchesMonitor::tryStartMatch(PlayerID_t matchID) {
    std::unique_lock<std::mutex> lck(m);
    auto it = matches.find(matchID);
    bool started = false;
    if (it == matches.end()) {
        std::cerr << "ERROR: Trying to start match with ID: " << matchID << " which wasnt found.\n";
    } else if (!(it->second->hasEnoughPlayers())) {
        std::cerr << "ERROR: Trying to start match with ID: " << matchID
                  << " which doesnt have enough players to be started.\n";
    } else {
        it->second->start();
        started = true;
    }
    return started;
}

void MatchesMonitor::logOutPlayer(PlayerID_t matchID, PlayerID_t player) {
    std::unique_lock<std::mutex> lck(m);
    auto it = matches.find(matchID);
    if (it == matches.end()) {
        std::cerr << "ERROR: Trying to logout player [ID:" << player
                  << "] from match [ID: " << matchID << "] but match wasnt found on the server.\n";
        return;
    }
    it->second->logOutPlayer(player);
}

void MatchesMonitor::forceEndAllMatches() {
    std::unique_lock<std::mutex> lck(m);
    for (auto& pair: matches) {
        pair.second->forceEnd();
    }
}

void MatchesMonitor::forceEndMatch(PlayerID_t matchID) {
    std::unique_lock<std::mutex> lck(m);
    auto it = matches.find(matchID);
    if (it == matches.end()) {
        std::cerr << "ERROR: Trying to specifically end the match [ID:" << matchID
                  << "] wich could be found in the matches in the server.\n";
        return;
    }
    it->second->forceEnd();
}
