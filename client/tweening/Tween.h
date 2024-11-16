#ifndef TWEEN_H
#define TWEEN_H

#include <functional>

using OnCompleteCallback = std::function<void()>;

class Tween {
protected:
    float duration;
    float timming;
    OnCompleteCallback onComplete;
    bool alive;
    bool started;

public:
    explicit Tween(float duration, OnCompleteCallback onComplete = nullptr);
    virtual ~Tween();

    void Play();

    virtual void Update(float deltaTime);
    virtual void DoTween(float deltaTime) = 0;

    float InverseLerp(float a, float b, float x);
    float DecreaseTiming(float deltaRime);
};

#endif
