#ifndef CAMERA_H
#define CAMERA_H

#include <algorithm>
#include <list>
#include <string>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "cache/TextureCache.h"
#include "common/Transform.h"
#include "common/Vector2D.h"
#include "gui/RectTransform.h"

#include "ColorExtension.h"
#include "Rate.h"

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
    ~Camera();

    void Clean();
    void Render();
    void SetPos(Vector2D position);
    Vector2D GetPos();
    void SetSize(float size);
    float GetSize();

    void InitRate();
    float GetRateDeltatime();
    void Delay();

    void ClearCacheItem(const string& filename);

    void DrawTexture(const string& filename, SDL2pp::Optional<Rect> sourceRect,
                     const Transform& transform, Color color = ColorExtension::White(),
                     bool flip = false);

    void DrawTexture(const string& filename, SDL2pp::Optional<Rect> sourceRect, Color color,
                     const Transform& transform, int flip);

    void DrawGUI(RectTransform rect, Color color);

    void DrawImageGUI(const string& filename, RectTransform rect, SDL2pp::Optional<Rect> srcRect,
                      Color color = ColorExtension::White(), bool flip = false);

    void DrawText(const string& text, SDL2pp::Font& font, RectTransform rectTransform, Color color);

    Rect RectTransformToRenderRect(RectTransform& rectTransform);

    Vector2D ScreenToWorldPoint(Vector2D screenPos);
};

#endif
