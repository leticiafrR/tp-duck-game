#include "ImageTween.h"

ImageTween::ImageTween(std::optional<Image*> img): Tween(1.0f, []() {}), img(img) {
    if (img.has_value()) {
        startColor = img.value()->GetColor();
        targetColor = img.value()->GetColor();
    }
}


ImageTween::ImageTween(std::optional<Image*> img, Color targetColor, float duration,
                       OnCompleteCallback onComplete):
        Tween(duration, onComplete), img(img) {
    if (img.has_value()) {
        startColor = img.value()->GetColor();
        this->targetColor = targetColor;
    }
}

ImageTween::~ImageTween() = default;

void ImageTween::OnInitLoop() {}

void ImageTween::DoTween(float t) {
    if (!img.has_value())
        return;
    img.value()->SetColor(ColorExtension::Lerp(startColor, targetColor, t));
}
