#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <map>
#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "multimedia/2d/Object2D.h"
#include "multimedia/cache/SheetDataCache.h"

using SDL2pp::Rect;

class Animator {
private:
    Object2D& sprite;
    std::map<std::string, std::vector<Rect>> animations;
    std::string target;
    int frameIndex;

    float animFrameTime;
    float updateTimer;

public:
    Animator(Object2D& spr, const std::string& filename, const std::string& target, int targetFPS);

    ~Animator();

    void Update(float deltaTime);

    Rect GetTargetRect();

    void SetTarget(const std::string& target, bool reset_index = true);

    std::string GetTarget();
};

#endif
