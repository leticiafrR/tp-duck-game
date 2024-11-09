#ifndef ROUND_H
#define ROUND_H
#include <unordered_map>

#include "data/dataTransferObjects.h"
#include "data/groundDta.h"

class Round {
private:
    GameSceneDto settings;
    //[[clang::supress_unused]] std::unordered_map<PlayerID_t, Vector2D> positions;

public:
    explicit Round(GameSceneDto& settings);
    // void UpdateRound(Snapshot& ss);
};

#endif
