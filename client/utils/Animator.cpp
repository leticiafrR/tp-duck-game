#include "Animator.h"

Animator::Animator() = default;

Animator::Animator(const std::string& target, const unordered_map<string, vector<Rect>>& frames,
                   int targetFPS):
        frames(frames) {
    frameIndex = 0;
    this->target = target;

    animFrameTime = 1.0f / targetFPS;
    updateTimer = animFrameTime;
}

Animator::~Animator() = default;

void Animator::Update(float deltaTime, Object2D& obj) {
    updateTimer -= deltaTime;
    if (updateTimer <= 0) {
        updateTimer = animFrameTime;
        frameIndex += 1;
        frameIndex = (frameIndex % frames[target].size());
    }
    obj.SetSourceRect(GetTargetRect());
}

Rect Animator::GetTargetRect() { return frames[target][frameIndex]; }

void Animator::SetTarget(const std::string& target, bool reset_index) {
    if (!TargetExists(target))
        return;
    this->target = target;
    if (reset_index) {
        updateTimer = animFrameTime;
        frameIndex = 0;
    }
}

bool Animator::TargetExists(const std::string& target) { return frames.contains(target); }

std::string Animator::GetTarget() { return target; }
