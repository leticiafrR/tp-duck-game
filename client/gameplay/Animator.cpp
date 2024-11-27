#include "Animator.h"

Animator::Animator(Object2D& spr, const std::string& filename, const std::string& target,
                   int targetFPS):
        sprite(spr), animations(std::move(SheetDataCache::GetData(filename))) {
    frameIndex = 0;
    this->target = target;

    animFrameTime = 1.0f / targetFPS;
    updateTimer = animFrameTime;
}

Animator::~Animator() = default;

void Animator::Update(float deltaTime) {
    updateTimer -= deltaTime;
    if (updateTimer <= 0) {
        updateTimer = animFrameTime;
        frameIndex += 1;
        frameIndex = (frameIndex % animations[target].size());
    }
    sprite.SetSourceRect(GetTargetRect());
}

Rect Animator::GetTargetRect() { return animations[target][frameIndex]; }

void Animator::SetTarget(const std::string& target, bool reset_index) {
    if (!animations.contains(target))
        return;
    this->target = target;
    if (reset_index) {
        updateTimer = animFrameTime;
        frameIndex = 0;
    }
}

std::string Animator::GetTarget() { return target; }
