#ifndef OBJECT_2D_H
#define OBJECT_2D_H

#include <algorithm>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "common/Transform.h"

using SDL2pp::Color;
using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::Texture;
using std::string;

class Object2D {
private:
    Texture tex;
    SDL2pp::Optional<Rect> sourceRect;

    Transform transform;

    bool flipH = false;

public:
    Object2D(Renderer& render, const Transform& transform, const std::string& filename);

    void SetColor(Color color);

    Transform& GetTransform() { return this->transform; }

    Texture& GetTexture() { return tex; }

    void SetSourceRect(const SDL2pp::Optional<Rect>& rect) { this->sourceRect = rect; }
    SDL2pp::Optional<Rect> GetSourceRect() { return this->sourceRect; }

    void SetHorizontalFlip(bool flipH) { this->flipH = flipH; }

    int GetFlipSDL() { return flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE; }

    ~Object2D();

    Object2D(const Object2D&) = default;
    Object2D& operator=(const Object2D&) = default;

    Object2D(Object2D&& other) = default;
    Object2D& operator=(Object2D&& other) = default;
};

Object2D::Object2D(Renderer& render, const Transform& transform, const string& filename):
        tex(render, filename), sourceRect(SDL2pp::NullOpt), transform(transform) {}

void Object2D::SetColor(Color color) { tex.SetColorAndAlphaMod(color); }

Object2D::~Object2D() {}

#endif
