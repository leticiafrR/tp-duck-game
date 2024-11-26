#ifndef CAMERA_H
#define CAMERA_H

#include <algorithm>
#include <list>
#include <string>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "common/Transform.h"
#include "common/Vector2D.h"

#include "Rate.h"
#include "RectTransform.h"
#include "TextureCache.h"

using namespace SDL2pp;  // NOLINT
using std::string;

class Camera {
private:
    Renderer render;
    TextureCache textureCache;
    Vector2D position;

    float size;
    Rate rate;

public:
    Camera(Renderer render, float size, Rate rate);
    void Clean() { render.Clear(); }
    void Render();
    void SetPos(Vector2D position) { this->position = position; }
    Vector2D GetPos() { return position; }
    void SetSize(float size) { this->size = size; }
    float GetSize() { return this->size; }
    ~Camera();

    void DrawTexture(const string& filename, SDL2pp::Optional<Rect> sourceRect, Color color,
                     const Transform& transform, int flip);

    void DrawGUI(RectTransform rect, Color color);

    void DrawImageGUI(const string& filename, RectTransform rect, SDL2pp::Optional<Rect> srcRect,
                      Color color, bool flip);

    void DrawText(const string& text, SDL2pp::Font& font, RectTransform rectTransform, Color color);

    Rect RectTransformToRenderRect(RectTransform& rectTransform);

    void ClearCacheItem(const string& filename);

    float GetRateDeltatime() { return rate.GetDeltaTime(); }

    float GetRateMiliseconds() { return rate.GetMiliseconds(); }

    void Delay() { SDL_Delay(GetRateMiliseconds()); }
};

#endif
