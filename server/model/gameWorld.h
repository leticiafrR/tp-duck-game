#ifndef GAME_WORLD_
#define GAME_WORLD_

#include <string>
#include <vector>

#include "../common/Transform.h"
#include "../common/command.h"
#include "../common/snapShoot.h"
#include "../data/id.h"


/* API required to the match */
class GameWorld {

public:
    /* must parse (use a parser) the name of the file received to build the platforms*/
    explicit GameWorld(std::string levelName, std::vector<PlayerID_t> playerIds);

    std::vector<Transform>& getGamePlatforms();

    void handleCommand(Command cmmd);
    void update();
    SnapShoot getSnapshoot();

    bool hasWinner();

    PlayerID_t whoWon();
};


#endif
