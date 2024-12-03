#ifndef IMAGE_TWEEN_H
#define IMAGE_TWEEN_H

#include <memory>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "multimedia/ColorExtension.h"
#include "multimedia/gui/Image.h"

#include "Tween.h"

class ImageTween: public Tween {
private:
    std::optional<Image*> img;
    Color startColor;
    Color targetColor;

public:
    explicit ImageTween(std::optional<Image*> img = std::nullopt);

    ImageTween(
            std::optional<Image*> img, Color targetColor, float duration,
            OnCompleteCallback onComplete = []() {});

    void OnInitLoop() override;

    void DoTween(float t) override;

    ~ImageTween();
};

#endif
