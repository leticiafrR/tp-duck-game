#ifndef GAME_H
#define GAME_H

#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../data/command.h"
#include "event/EventsManager.h"
#include "map/staticMap.h"

#include "Duck.h"

#define ID_PLAYER_UNIQUE_TEST 1
class GameWorld {
private:
    size_t livePlayers;
    StaticMap map;
    std::unordered_map<PlayerID_t, Duck*> players;
    std::set<ObjectID_t> uniquesIds;
    EventsManager eventsManager;
    void ReapDead();
    void Testing(const Vector2D& posToTest);
    void CreatePlayers(const std::vector<PlayerID_t>& playersIds);

public:
    explicit GameWorld(const Vector2D& posToTest = Vector2D(INFINITY, INFINITY),
                       const std::vector<PlayerID_t>& playersIds = {ID_PLAYER_UNIQUE_TEST},
                       const std::string& sceneName = "");
    GameSceneDto getSceneDto();

    void HandleCommand(const Command& cmd);
    void Update(float deltaTime);
    bool HasWinner();
    bool IsOver();
    PlayerID_t WhoWon();
    Snapshot GetSnapshot();

    // void quitPlayer(PlayerID_t);
    ~GameWorld();
};
#endif
