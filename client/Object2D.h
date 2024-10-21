#ifndef OBJECT_2D_H
#define OBJECT_2D_H

#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "Transform.h"

#define RGBA(r, g, b, a) r, g, b, a
static const unsigned char pixels[4] = {RGBA(0xff, 0xff, 0xff, 0xff)};

class Object2D {
private:
    SDL2pp::Texture tex;
    Transform transform;

public:
    Object2D(SDL2pp::Renderer& render, const Transform& transform);

    void SetColor(SDL2pp::Color color);

    Transform& GetTransform() { return this->transform; }

    SDL2pp::Texture& GetTexture() { return tex; }

    ~Object2D();

    Object2D(const Object2D&) = default;
    Object2D& operator=(const Object2D&) = default;

    Object2D(Object2D&& other) = default;
    Object2D& operator=(Object2D&& other) = default;
};

Object2D::Object2D(SDL2pp::Renderer& render, const Transform& transform):
        tex(render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 1, 1),
        transform(transform) {
    tex.Update(SDL2pp::NullOpt, pixels, 1);
}

void Object2D::SetColor(SDL2pp::Color color) { tex.SetColorAndAlphaMod(color); }

Object2D::~Object2D() {}

#endif
