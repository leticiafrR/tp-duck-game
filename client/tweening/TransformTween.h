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
    explicit TransformTween(Transform& t):
            Tween(1.0f, []() {}),
            transform(t),
            startSize(transform.GetSize()),
            targetSize(transform.GetSize()) {}

    TransformTween(
            Transform& transform, Vector2D targetSize, float duration,
            OnCompleteCallback onComplete = []() {}):
            Tween(duration, onComplete),
            transform(transform),
            startSize(transform.GetSize()),
            targetSize(targetSize) {}

    void SetTarget(
            Vector2D targetSize, float duration, OnCompleteCallback onComplete = []() {}) {
        this->targetSize = targetSize;
        this->duration = duration;
        this->onComplete = onComplete;
    }

    void OnInitLoop() override {
        switch (loopType) {
            case LoopType::Restart:
                transform.SetSize(startSize);
                break;
            case LoopType::Yoyo:
                changed = false;
                Vector2D tmp = startSize;
                startSize = targetSize;
                targetSize = tmp;
                break;
        }
    }

    void DoTween(float t) override {
        switch (loopType) {
            case LoopType::Restart:

                break;
            case LoopType::Yoyo:

                if (t >= 0.5f && !changed) {
                    changed = true;
                    Vector2D tmp = startSize;
                    startSize = targetSize;
                    targetSize = tmp;
                }
                if (!changed)
                    t = InverseLerp(0.0f, 0.5f, t);
                else
                    t = InverseLerp(0.5f, 1.0f, t);
                break;
            default:
                break;
        }
        transform.SetSize(Vector2D::Lerp(startSize, targetSize, t));
    }

    ~TransformTween() = default;
};

#endif
