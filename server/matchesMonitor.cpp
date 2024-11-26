#include "matchesMonitor.h"

#include "data/dataMatch.h"
#include "data/errorCodesJoinMatch.h"

MatchesMonitor::MatchesMonitor(const Config& config): config(config) {}


void MatchesMonitor::reapEndedMatches() {
    std::unique_lock<std::mutex> lck(m);
    for (auto it = matches.begin(); it != matches.end();) {
        if ((it->second)->isOver()) {
            if (matches[it->first]->hadStarted()) {
                matches[it->first]->join();
            }
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

std::shared_ptr<Queue<Command>> MatchesMonitor::tryJoinMatch(
        uint16_t matchID, Queue<std::shared_ptr<MessageSender>>* clientQueue,
        const ClientInfo& clientInfo, uint8_t& eCode) {

    std::unique_lock<std::mutex> lck(m);
    auto it = matches.find(matchID);
    if (it != matches.end()) {
        return matches[matchID]->logInClient(clientInfo, clientQueue, eCode);
    }
    if (matchID == clientInfo.connectionId) {
        matches.emplace(matchID, std::make_unique<Match>(config, matchID));
        auto matchQueue = matches[matchID]->logInClient(clientInfo, clientQueue, eCode);
        if (matchQueue == nullptr) {

            matches.erase(matchID);
            return nullptr;
        }
        return matchQueue;
    }
    eCode = E_CODE::NOT_FOUND;
    return nullptr;
}

bool MatchesMonitor::tryStartMatch(uint16_t matchID) {
    std::unique_lock<std::mutex> lck(m);
    auto it = matches.find(matchID);
    if (it != matches.end() && it->second->readyToStart()) {
        it->second->start();
        return true;
    }
    return false;
}

void MatchesMonitor::logOutClient(uint16_t matchID, uint16_t clientID) {
    std::unique_lock<std::mutex> lck(m);
    auto it = matches.find(matchID);
    if (it != matches.end())
        it->second->logOutClient(clientID);
}

void MatchesMonitor::forceEndAllMatches() {
    std::unique_lock<std::mutex> lck(m);
    for (auto& pair: matches) {
        pair.second->forceEnd();
    }
}

void MatchesMonitor::forceEndMatch(uint16_t matchID) {
    std::unique_lock<std::mutex> lck(m);
    auto it = matches.find(matchID);
    if (it != matches.end())
        it->second->forceEnd();
}
