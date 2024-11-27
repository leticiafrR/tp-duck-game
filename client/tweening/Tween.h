#ifndef TWEEN_H
#define TWEEN_H

#include <functional>

#include "multimedia/Definitions.h"

using OnCompleteCallback = Callback;

enum class LoopType { Restart, Yoyo };

class Tween {
protected:
    float duration;
    float timming;
    OnCompleteCallback onComplete;
    bool alive;
    bool started;

    int loopsCounter = 0;
    int loops = 1;
    LoopType loopType = LoopType::Restart;

public:
    explicit Tween(float duration, OnCompleteCallback onComplete = nullptr);
    virtual ~Tween();

    void Play();

    void SetLoops(int loops, LoopType loopType) {
        this->loops = loops;
        this->loopType = loopType;
    }

    virtual void Update(float deltaTime);
    virtual void DoTween(float deltaTime) = 0;
    virtual void OnInitLoop() = 0;

    float InverseLerp(float a, float b, float x);
    float DecreaseTiming(float deltaRime);
};

#endif
