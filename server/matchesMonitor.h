#ifndef MATCHES_MONITOR_
#define MATCHES_MONITOR_
#include <memory>
#include <unordered_map>
#include <vector>

#include "match.h"
// (getAvailableMatches() metodo protegido del monitor -> acceso de lectura a los status de las
// matches
// -> debe ser mutuamente excluyente con waitingForMatchStarting-> acceso de escritura al status de
// la match (si es el player creador)

// crear una partida nueva -> acceso de escritura al container con
// cambio de available a on course -> acceso de escritur

class MatchesMonitor {
private:
    // This should have access to the quantity of players in the match. Also im thinking about
    // taking out of the match the resposability of starting it self
    // cppcheck-suppress unusedStructMember
    std::unordered_map<PlayerID_t, Match*> availableMatches;
    // cppcheck-suppress unusedStructMember
    std::unordered_map<PlayerID_t, Match*> matchesOncourse;
    std::mutex available;
    std::mutex onCourse;  // es inecesario
    // cppcheck-suppress unusedStructMember
    Config configuration;

public:
    explicit MatchesMonitor(const Config& _configuration);
    std::shared_ptr<Queue<Command>> tryJoinMatch(const PlayerID_t& id);  // si no existe la creo
    void transferStaredMatch(PlayerID_t ID);
    void stopAllMatches();
    void stopAMatch(const PlayerID_t& id);
    void StartAMatch(const PlayerID_t& id);
    void LogOutPlayer(const PlayerID_t& playerID, const PlayerID_t& matchID);
    std::vector<ActiveMatch> getAvailableMatches();  // creo que convendria enviar ya la informacion
                                                     // que recibe el protocolo
    ~MatchesMonitor();
};
#endif
