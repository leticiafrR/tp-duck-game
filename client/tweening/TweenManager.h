#ifndef TWEEN_MANAGER_H
#define TWEEN_MANAGER_H

#include <algorithm>
#include <vector>

#include "Tween.h"

class TweenManager {
private:
    TweenManager() = default;
    std::vector<Tween*> tweens;

public:
    static TweenManager& GetInstance() {
        static TweenManager Instance;
        return Instance;
    }

    void AddTween(Tween* tw) { tweens.push_back(tw); }

    void RemoveTween(Tween* tw) {
        auto it = std::find(tweens.begin(), tweens.end(), tw);
        if (it != tweens.end()) {
            tweens.erase(it);
        }
    }

    void Update(float deltaTime) {
        for (auto tw: tweens) {
            tw->Update(deltaTime);
        }
    }

    // Remove copy
    TweenManager(const TweenManager&) = delete;
    TweenManager& operator=(const TweenManager&) = delete;

    ~TweenManager() = default;
};


#endif
