#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "multimedia/2d/Object2D.h"

using SDL2pp::Rect;
using std::string;
using std::unordered_map;
using std::vector;

class Animator {
private:
    unordered_map<string, vector<Rect>> frames;
    string target;
    int frameIndex;

    float animFrameTime;
    float updateTimer;

public:
    Animator();
    Animator(const std::string& target, const unordered_map<string, vector<Rect>>& frames,
             int targetFPS);

    ~Animator();

    void Update(float deltaTime, Object2D& sprite);

    bool TargetExists(const std::string& target);

    Rect GetTargetRect();

    void SetTarget(const std::string& target, bool reset_index = true);

    std::string GetTarget();
};

#endif
