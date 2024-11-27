#include "ImageTween.h"

ImageTween::ImageTween(Image& img, Color targetColor, float duration,
                       OnCompleteCallback onComplete):
        Tween(duration, onComplete),
        img(img),
        startColor(img.GetColor()),
        targetColor(targetColor) {}

ImageTween::~ImageTween() = default;

void ImageTween::OnInitLoop() {}

void ImageTween::DoTween(float t) {
    img.SetColor(ColorExtension::Lerp(startColor, targetColor, t));
}
