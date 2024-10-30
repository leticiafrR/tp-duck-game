#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <map>
#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "AnimationParser.h"
#include "Object2D.h"

using SDL2pp::Rect;

class Animator {
private:
    int frameIndex;

    std::string target;
    Rect currentFrameRect;

public:
    std::map<std::string, std::vector<Rect>> animations;
    explicit Animator(const std::string& target) {
        frameIndex = 0;
        this->target = target;
    }

    Animator(const std::string& filename, const std::string& target):
            animations(std::move(AnimationParser::ParseAnimationData(filename))) {
        frameIndex = 0;
        this->target = target;
    }

    ~Animator() = default;

    void Update() {
        frameIndex += 1;
        frameIndex = (frameIndex % animations[target].size());
    }

    Rect GetTargetRect() { return animations[target][frameIndex]; }

    void SetTarget(const std::string& target, bool reset_index = true) {
        this->target = target;
        if (reset_index)
            frameIndex = 0;
    }
};

#endif
