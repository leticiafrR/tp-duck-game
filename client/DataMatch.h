#ifndef DATAMATCH_H
#define DATAMATCH_H
#include <mutex>

#include "data/dataTransferObjects.h"

#include "round.h"
class DataMatch {
private:
    std::mutex mtx;
    Round actualRound;
    PlayerID_t winner;
    MatchStartDto settings;
    GameSceneDto scene;
    // Snapshot snapshot;
    GamesRecountDto counts;

public:
    DataMatch();
    // RestartMatch();
    void SetStartMatchSettings(const MatchStartDto& stgs) { settings = stgs; }
    void RestartGame(const GameSceneDto& settings) { scene = settings; }  // replace o new

    /*void UpdateGame(const Snapshot& snapshot) {
        std::lock_guard<std::mutex> lck(mtx);
        actualRound.UpdateRound(snapshot);
    }*/
    MatchStartDto GetMatchStartDto() {
        std::lock_guard<std::mutex> lck(mtx);
        return settings;
    }

    GameSceneDto GetScene() {
        std::lock_guard<std::mutex> lck(mtx);
        return scene;
    }
    /*Snapshot GetSnapshot(){
        std::lock_guard<std::mutex> lck(mtx);
        return snapshot;
    }*/

    void SettWinner(const PlayerID_t win) {
        std::lock_guard<std::mutex> lck(mtx);
        winner = win;
    }

    PlayerID_t GetWinner() {
        std::lock_guard<std::mutex> lck(mtx);
        return winner;
    }

    void SetRecount(const GamesRecountDto& count) {
        std::lock_guard<std::mutex> lck(mtx);
        counts = count;
    }
};
#endif
