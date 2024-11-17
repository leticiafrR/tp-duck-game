#ifndef LOBBY_H_
#define LOBBY_H_
#include <memory>

#include "../common/thread.h"

#include "matchesMonitor.h"
#include "serverProtocol.h"
// your code here (XD)
class Lobby: public Thread {
private:
    MatchesMonitor& monitor;
    PlayerID_t& playerID;
    Queue<std::shared_ptr<MessageSender>>& senderQueue;
    ServerProtocol& protocol;  // hay un lobby por cliente
    std::atomic<bool> _joinedAMatch;
    std::shared_ptr<Queue<Command>>& matchQueue;

public:
    explicit Lobby(MatchesMonitor& _monitor, std::atomic<bool>& _joinedAMatch, const PlayerID_t _id,
                   Queue<std::shared_ptr<MessageSender>> _senderQueue, ServerProtocol& _protocol,
                   std::shared_ptr<Queue<Command>>& _matchQueue);
    void run() override;
    void waitingStartMatch();
    // not copyable
    Lobby(const Lobby&) = delete;
    Lobby& operator=(const Lobby&) = delete;

    // not movable
    Lobby(Lobby&&) = delete;
    Lobby& operator=(Lobby&&) = delete;
}
// lobby.getMatchID()-> solo seteado si no se desconectò antes de unirse a una partida
#endif
