#ifndef MATCHBINDER_H_
#define MATCHBINDER_H_
#include <memory>

#include "common/thread.h"
#include "server/matchesMonitor.h"

#include "serverProtocol.h"
// your code here (XD)
class MatchBinder {
private:
    MatchesMonitor& monitor;
    const PlayerID_t& playerID;
    Queue<std::shared_ptr<MessageSender>>& senderQueue;
    ServerProtocol& protocol;  // hay un MatchBinder por cliente
    // cppcheck-suppress unusedStructMember
    bool _joinedAMatch;
    std::shared_ptr<Queue<Command>>& matchQueue;

public:
    explicit MatchBinder(MatchesMonitor& _monitor, bool _joinedAMatch, const PlayerID_t& _id,
                         Queue<std::shared_ptr<MessageSender>> _senderQueue,
                         ServerProtocol& _protocol, std::shared_ptr<Queue<Command>>& _matchQueue);
    void bind();
    void waitingStartMatch();
    // not copyable
    MatchBinder(const MatchBinder&) = delete;
    MatchBinder& operator=(const MatchBinder&) = delete;

    // not movable
    MatchBinder(MatchBinder&&) = delete;
    MatchBinder& operator=(MatchBinder&&) = delete;
};
// MatchBinder.getMatchID()-> solo seteado si no se desconectò antes de unirse a una partida
#endif
