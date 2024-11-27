#ifndef TWEEN_MANAGER_H
#define TWEEN_MANAGER_H

#include <algorithm>
#include <vector>

#include "Tween.h"

class TweenManager {
private:
    std::vector<Tween*> tweens;
    TweenManager();

public:
    static TweenManager& GetInstance();
    ~TweenManager();
    void AddTween(Tween* tw);

    void RemoveTween(Tween* tw);

    void Update(float deltaTime);

    // Remove copy
    TweenManager(const TweenManager&) = delete;
    TweenManager& operator=(const TweenManager&) = delete;
};


#endif
