#ifndef MATCH_H
#define MATCH_H

#include <string>

struct Match {
    bool newMatch;  // Se podria definir una estructura especifica ya que esto solo se usaria cuando
    std::string matchName;
    std::string clientName;
    size_t id;
}
#endif
