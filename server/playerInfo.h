#ifndef PLAYER_INFO_
#define PLAYER_INFO_

#include <memory>
#include <string>

#include "common/queue.h"

class MessageSender;

struct PlayerInfo {
    std::string nickname;
    // cppcheck-suppress unusedStructMember
    Queue<std::shared_ptr<MessageSender>>* senderQueue;
};

#endif
