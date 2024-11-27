#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <map>
#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "multimedia/Object2D.h"
#include "multimedia/SheetDataCache.h"

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
    Animator(Object2D& spr, const std::string& filename, const std::string& target, int targetFPS):
            sprite(spr), animations(std::move(SheetDataCache::GetData(filename))) {
        frameIndex = 0;
        this->target = target;

        animFrameTime = 1.0f / targetFPS;
        updateTimer = animFrameTime;
    }

    ~Animator() = default;

    void Update(float deltaTime) {
        // std::cout <<  frameIndex << "\n";

        updateTimer -= deltaTime;
        if (updateTimer <= 0) {
            updateTimer = animFrameTime;
            frameIndex += 1;
            frameIndex = (frameIndex % animations[target].size());
        }
        // std::cout <<  sprite.GetFileName() << "\n";
        sprite.SetSourceRect(GetTargetRect());
    }

    Rect GetTargetRect() { return animations[target][frameIndex]; }

    void SetTarget(const std::string& target, bool reset_index = true) {
        if (!animations.contains(target))
            return;
        this->target = target;
        if (reset_index) {
            updateTimer = animFrameTime;
            frameIndex = 0;
        }
    }

    std::string GetTarget() { return target; }
};

#endif
