#ifndef IMAGE_TWEEN_H
#define IMAGE_TWEEN_H

#include <memory>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "../ColorExtension.h"
#include "../Image.h"

#include "Tween.h"

class ImageTween: public Tween {
private:
    Image& img;
    Color startColor;
    Color targetColor;

public:
    ImageTween(
            Image& img, Color targetColor, float duration, OnCompleteCallback onComplete = []() {}):
            Tween(duration, onComplete),
            img(img),
            startColor(img.GetColor()),
            targetColor(targetColor) {}

    void DoTween(float t) override {
        img.SetColor(ColorExtension::Lerp(startColor, targetColor, t));
    }

    ~ImageTween() = default;
};

#endif
