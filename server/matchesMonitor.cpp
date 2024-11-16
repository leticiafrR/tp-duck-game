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

void MatchesMonitor::waitForMatchStarting(const ID_player& playerID, const ID_Match& matchID) {
    if (playerID != matchID) {
        std::unique_lock<std::mutex> lock(
                available);  //-> mutex para el acceso a las available matches
        availableMatches[playerID].waitForMatchStarting(playerID);
        transferStaredMatch(matchID);
    } else {
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


std::vector<ActiveMatch> MatchesMonitor::getAvailableMatches() {
    std::unique_lock<std::mutex> lock(available);
    std::vector<ActiveMatch> data;
    std::transform(matches.begin(), matches.end(), std::back_inserter(data),
                   [](const auto& match) { return match.second->getDataMatch(); });
    return data;
}  // creo que convendria enviar ya la informacion que recibe el protocolo

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
