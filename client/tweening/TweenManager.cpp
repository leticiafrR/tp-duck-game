#include "TweenManager.h"

TweenManager::TweenManager() = default;

TweenManager::~TweenManager() = default;

TweenManager& TweenManager::GetInstance() {
    static TweenManager Instance;
    return Instance;
}

void TweenManager::AddTween(Tween* tw) { tweens.push_back(tw); }

void TweenManager::RemoveTween(Tween* tw) {
    auto it = std::find(tweens.begin(), tweens.end(), tw);
    if (it != tweens.end()) {
        tweens.erase(it);
    }
}

void TweenManager::Update(float deltaTime) {
    for (auto tw: tweens) {
        tw->Update(deltaTime);
    }
}
