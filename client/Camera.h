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

#include "TextureCache.h"

using SDL2pp::Color;
using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::Texture;
using std::string;

class Camera {
private:
    Renderer render;
    TextureCache textureCache;
    Vector2D position;

    float size;

public:
    Camera(Renderer render, float size);
    void Clean() { render.Clear(); }
    void Render();
    void SetPos(Vector2D position) { this->position = position; }
    Vector2D GetPos() { return position; }
    void SetSize(float size) { this->size = size; }
    float GetSize() { return this->size; }
    ~Camera();

    void DrawTexture(const string& filename, SDL2pp::Optional<Rect> sourceRect, Color color,
                     const Transform& transform, int flip);

    void DrawGUI(Rect rect, Color color);

    void DrawText(const string& text, SDL2pp::Font& font, SDL2pp::Point point, Color color);
};

#endif
