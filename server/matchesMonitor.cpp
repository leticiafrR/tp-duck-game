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
        }
        return matchQueue;
    }
    eCode = E_CODE::NOT_FOUND;
    std::cerr << "-Client trying to join a match that doesnt exist, but MatchID is different from "
                 "playerID .\n";
    return nullptr;
}

bool MatchesMonitor::tryStartMatch(uint16_t matchID) {
    bool started = false;
    std::unique_lock<std::mutex> lck(m);
    auto it = matches.find(matchID);
    if (it == matches.end()) {
        std::cerr << "ERROR: Trying to start match with ID: " << matchID << " which wasnt found.\n";
    } else if (!(it->second->readyToStart())) {
        std::cerr << "-Client Trying to start match with ID: " << matchID
                  << " but doesnt have enough players.\n";
    } else {
        it->second->start();
        started = true;
    }
    return started;
}

void MatchesMonitor::logOutClient(uint16_t matchID, uint16_t clientID) {
    std::unique_lock<std::mutex> lck(m);
    auto it = matches.find(matchID);
    if (it == matches.end()) {
        std::cerr << "ERROR: Trying to log out client [ID:" << clientID
                  << "] from match [ID: " << matchID << "] but match wasnt found on the server.\n";
        return;
    }
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
    if (it == matches.end()) {
        std::cerr << "ERROR: Trying to specifically end the match [ID:" << matchID
                  << "] that was not found on the server.\n";
        return;
    }
    it->second->forceEnd();
}
