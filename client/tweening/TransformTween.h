#ifndef TRANSFORM_TWEEN_H
#define TRANSFORM_TWEEN_H

#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "../../common/Transform.h"

#include "Tween.h"

class TransformTween: public Tween {
private:
    Transform& transform;
    Vector2D startSize;
    Vector2D targetSize;

    bool changed = false;

public:
    explicit TransformTween(Transform& t);

    TransformTween(
            Transform& transform, Vector2D targetSize, float duration,
            OnCompleteCallback onComplete = []() {});

    void SetTarget(
            Vector2D targetSize, float duration, OnCompleteCallback onComplete = []() {});

    void OnInitLoop() override;

    void DoTween(float t) override;

    ~TransformTween();
};

#endif
