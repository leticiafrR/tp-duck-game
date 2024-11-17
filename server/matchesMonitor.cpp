#include "matchesMonitor.h"

#include <algorithm>
#include <memory>
#include <vector>

#include "match.h"

MatchesMonitor::MatchesMonitor(const Config& _configuration):
        availableMatches(), matchesOncourse(), configuration(_configuration) {}

std::shared_ptr<Queue<Command>> MatchesMonitor::tryJoinMatch(const PlayerID_t& id) {
    std::unique_lock<std::mutex> lock(available);

    if (availableMatches.find(id) == availableMatches.end() &&
        matchesOncourse.find(id) != matchesOncourse.end()) {
        return std::nullopt;
    } else if (availableMatches.find(id) != availableMatches.end()) {

        return availableMatches[id]->logInPlayer(id);
    }

    availableMatches[id] = Match(configuration, id);
    return true;
}
void MatchesMonitor::stopAMatch(const PlayerID_t& id) {
    std::unique_lock<std::mutex> lck1(onCourse);
    if (matchesOncourse.find(id) != matchesOncourse.end()) {
        matchesOncourse[id]->forceEnd();
        return;
    }
    lck1.unlock();
    std::unique_lock<std::mutex> lck2(available);
    if (availableMatches.find(id) != availableMatches.end()) {
        availableMatches[id]->forceEnd();
    }
}

void MatchesMonitor::stopAllMatches() {
    std::unique_lock<std::mutex> lck1(available);
    for (auto availableMatch: availableMatches) {
        availableMatch.second->forceEnd();
    }
    lck1.unlock();

    std::unique_lock<std::mutex> lck2(onCourse);
    for (auto oncourseMatch: matchesOncourse) {
        oncourseMatch.second->forceEnd();
    }
}

void MatchesMonitor::transferStaredMatch(PlayerID_t id) {
    std::unique_lock<std::mutex> lock(available);
    std::unique_lock<std::mutex> lock(onCourse);
    if (availableMatches.find(id) != availableMatches.end()) {
        Match* match = availableMatches[id];
        availableMatches.erase(id);
        matchesOncourse[id] = match;
    }
}

void MatchesMonitor::StartAMatch(const PlayerID_t& id) {
    availableMatches[id]->start();
    transferStaredMatch(id);
}

std::vector<ActiveMatch> MatchesMonitor::getAvailableMatches() {
    std::unique_lock<std::mutex> lock(available);
    std::vector<ActiveMatch> data;
    std::transform(matches.begin(), matches.end(), std::back_inserter(data),
                   [](const auto& match) { return match.second->getDataMatch(); });
    return data;
}  // creo que convendria enviar ya la informacion que recibe el protocolo

void LogOutPlayer(const PlayerID_t& playerID, const PlayerID_t& matchID) {
    std::unique_lock<std::mutex> lck1(onCourse);
    if (matchesOncourse.find(matchID) != matchesOncourse.end()) {
        matchesOncourse[matchID].log;
        return;
    }
    lck1.unlock();
    std::unique_lock<std::mutex> lck2(available);
    if (availableMatches.find(matchID) != availableMatches.end()) {
        availableMatches[matchID]->forceEnd();
    }
}

~MatchesMonitor() {
    // Destruir todos los objetos 'Match' en availableMatches
    for (const auto& pair: availableMatches) {
        delete pair.second;  // Liberar la memoria
    }

    // Destruir todos los objetos 'Match' en matchesOncourse
    for (const auto& pair: matchesOncourse) {
        delete pair.second;  // Liberar la memoria
    }
}
