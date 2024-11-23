#ifndef OBJECT_2D_H
#define OBJECT_2D_H

#include <algorithm>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "common/Transform.h"

#include "Camera.h"

using SDL2pp::Color;
using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::Texture;
using std::string;

class Object2D {
private:
    string filename;
    SDL2pp::Optional<Rect> sourceRect;

    Transform transform;
    Color color;

    bool flipH = false;
    bool visible = true;

public:
    Object2D() {}
    Object2D(const std::string& filename, const Transform& transform,
             Color color = Color(255, 255, 255));

    void SetColor(Color color);
    Color GetColor();

    Transform& GetTransform() { return this->transform; }
    void SetTransform(Transform transform) { this->transform = transform; }

    std::string& GetFileName() { return filename; }
    void SetFileName(const std::string& filename) { this->filename = filename; }

    void SetSourceRect(const SDL2pp::Optional<Rect>& rect) { this->sourceRect = rect; }
    SDL2pp::Optional<Rect> GetSourceRect() { return this->sourceRect; }

    void SetFlip(bool flipH) { this->flipH = flipH; }
    bool GetFlip() { return flipH; }

    int GetFlipSDL() { return flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE; }

    void Draw(Camera& cam) {
        if (!visible)
            return;
        if (filename.empty())
            return;
        cam.DrawTexture(filename, sourceRect, color, transform, GetFlipSDL());
    }

    void SetVisible(bool visible) { this->visible = visible; }

    virtual ~Object2D();

    Object2D(const Object2D&) = default;
    Object2D& operator=(const Object2D&) = default;

    Object2D(Object2D&& other) = default;
    Object2D& operator=(Object2D&& other) = default;
};

Object2D::Object2D(const std::string& filename, const Transform& transform, Color color):
        filename(filename), sourceRect(SDL2pp::NullOpt), transform(transform), color(color) {}

void Object2D::SetColor(Color color) { this->color = color; }
Color Object2D::GetColor() { return color; }

Object2D::~Object2D() {}

#endif
