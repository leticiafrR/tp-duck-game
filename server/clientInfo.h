#ifndef CLIENT_INFO_
#define CLIENT_INFO_

#include <cstdint>
#include <string>

struct ClientInfo {
    std::string baseNickname;
    // cppcheck-suppress unusedStructMember
    uint16_t connectionId;
    // cppcheck-suppress unusedStructMember
    uint8_t playersPerConnection;
};

#endif
