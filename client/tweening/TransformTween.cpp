#include "TransformTween.h"

TransformTween::TransformTween(Transform& t):
        Tween(1.0f, []() {}),
        transform(t),
        startSize(transform.GetSize()),
        targetSize(transform.GetSize()) {}

TransformTween::TransformTween(Transform& transform, Vector2D targetSize, float duration,
                               OnCompleteCallback onComplete):
        Tween(duration, onComplete),
        transform(transform),
        startSize(transform.GetSize()),
        targetSize(targetSize) {}

TransformTween::~TransformTween() = default;

void TransformTween::SetTarget(Vector2D targetSize, float duration, OnCompleteCallback) {
    this->targetSize = targetSize;
    this->duration = duration;
    this->onComplete = onComplete;
}

void TransformTween::OnInitLoop() {
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

void TransformTween::DoTween(float t) {
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
