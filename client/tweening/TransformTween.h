#ifndef TRANSFORM_TWEEN_H
#define TRANSFORM_TWEEN_H

#include <algorithm>
#include <optional>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "common/Transform.h"

#include "Tween.h"

class TransformTween: public Tween {
private:
    std::optional<Transform*> transform;
    Vector2D startSize;
    Vector2D targetSize;

    bool changed;

public:
    explicit TransformTween(std::optional<Transform*> t = std::nullopt);

    TransformTween(
            std::optional<Transform*> t, Vector2D targetSize, float duration,
            OnCompleteCallback onComplete = []() {});

    void SetTarget(
            Vector2D targetSize, float duration, OnCompleteCallback onComplete = []() {});

    void OnInitLoop() override;

    void DoTween(float t) override;

    ~TransformTween();
};

#endif
