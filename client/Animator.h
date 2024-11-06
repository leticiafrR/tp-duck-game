#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <map>
#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "Object2D.h"
#include "SheetDataCache.h"

using SDL2pp::Rect;

class Animator {
private:
    int frameIndex;

    float animFrameTime;
    float updateTimer;

    std::string target;
    Rect currentFrameRect;

public:
    std::map<std::string, std::vector<Rect>> animations;

    Animator(const std::string& filename, const std::string& target, int targetFPS):
            animations(std::move(SheetDataParser::GetData(filename))) {
        frameIndex = 0;
        this->target = target;

        animFrameTime = 1.0f / targetFPS;
        updateTimer = animFrameTime;
    }

    ~Animator() = default;

    void Update(float deltaTime) {
        updateTimer -= deltaTime;
        if (updateTimer <= 0) {
            updateTimer = animFrameTime;
            frameIndex += 1;
            frameIndex = (frameIndex % animations[target].size());
        }
    }

    Rect GetTargetRect() { return animations[target][frameIndex]; }

    void SetTarget(const std::string& target, bool reset_index = true) {
        this->target = target;
        if (reset_index) {
            updateTimer = animFrameTime;
            frameIndex = 0;
        }
    }
};

#endif
