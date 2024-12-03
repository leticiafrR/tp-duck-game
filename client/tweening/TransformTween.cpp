#include "TransformTween.h"

TransformTween::TransformTween(std::optional<Transform*> t):
        Tween(1.0f, []() {}), transform(t), changed(false) {
    if (transform.has_value()) {
        startSize = transform.value()->GetSize();
        targetSize = transform.value()->GetSize();
    } else {
        startSize = targetSize = Vector2D::Zero();
    }
}

TransformTween::TransformTween(std::optional<Transform*> t, Vector2D targetSize, float duration,
                               OnCompleteCallback onComplete):
        Tween(duration, onComplete), transform(t), changed(false) {
    if (transform.has_value()) {
        startSize = transform.value()->GetSize();
        this->targetSize = targetSize;
    } else {
        startSize = targetSize = Vector2D::Zero();
    }
}

TransformTween::~TransformTween() = default;

void TransformTween::SetTarget(Vector2D targetSize, float duration, OnCompleteCallback) {
    this->targetSize = targetSize;
    this->duration = duration;
    this->onComplete = onComplete;
}

void TransformTween::OnInitLoop() {
    if (!transform.has_value()) {
        return;
    }

    switch (loopType) {
        case LoopType::Restart:
            transform.value()->SetSize(startSize);
            break;
        case LoopType::Yoyo:
            changed = false;
            Vector2D tmp = startSize;
            startSize = targetSize;
            targetSize = tmp;
            break;
    }
}

void TransformTween::DoTween(float t) {
    if (!transform.has_value()) {
        return;
    }

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
    transform.value()->SetSize(Vector2D::Lerp(startSize, targetSize, t));
}
