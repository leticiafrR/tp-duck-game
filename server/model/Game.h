#ifndef GAME_H
#define GAME_H

#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "data/command.h"
#include "event/EventsManager.h"
#include "map/staticMap.h"
#include "projectile/ProjectilesController.h"

#include "Duck.h"
#define ID_PLAYER_UNIQUE_TEST 1
class GameWorld {
private:
    size_t livePlayers;
    StaticMap map;
    std::unordered_map<PlayerID_t, Duck*> players;
    EventsManager eventsManager;
    ProjectilesController p;
    void ReapDead();
    void Testing(const Vector2D& posToTest);
    void CreatePlayers(const std::vector<PlayerID_t>& playersIds);
    void ExecCommand(Duck* player, const CommandCode& code);

public:
    explicit GameWorld(const std::vector<PlayerID_t>& playersIds, const std::string& sceneName);
    GameSceneDto getSceneDto();

    void HandleCommand(const Command& cmd);
    void Update(float deltaTime);
    bool IsOver();
    PlayerID_t WhoWon();
    Snapshot GetSnapshot();

    // void quitPlayer(PlayerID_t);
    ~GameWorld();
};
#endif
