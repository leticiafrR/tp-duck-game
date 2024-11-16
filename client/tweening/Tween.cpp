#include "Tween.h"

#include <iostream>

#include "TweenManager.h"
Tween::Tween(float duration, OnCompleteCallback onComplete):
        duration(duration), timming(duration), onComplete(onComplete), alive(true), started(false) {
    TweenManager::GetInstance().AddTween(this);
}

Tween::~Tween() { TweenManager::GetInstance().RemoveTween(this); }

float Tween::InverseLerp(float a, float b, float x) { return (x - a) / (b - a); }
void Tween::Play() { started = true; }

void Tween::Update(float deltaTime) {
    if (!started || !alive)
        return;
    timming -= deltaTime;
    float t = InverseLerp(duration, 0, timming);
    DoTween(t);

    if (t >= 1.0f) {
        onComplete();
        alive = false;
    }
}

float Tween::DecreaseTiming(float deltaTime) {
    timming -= deltaTime;
    return InverseLerp(duration, 0, timming);
}
