#ifndef OBJECT_2D_H
#define OBJECT_2D_H

#include <algorithm>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "common/Transform.h"

using SDL2pp::Color;
using SDL2pp::Renderer;
using SDL2pp::Texture;
using std::string;

class Object2D {
private:
    Texture tex;
    Transform transform;

public:
    Object2D(Renderer& render, const Transform& transform, const std::string& filename);

    void SetColor(Color color);

    Transform& GetTransform() { return this->transform; }

    Texture& GetTexture() { return tex; }

    ~Object2D();

    Object2D(const Object2D&) = default;
    Object2D& operator=(const Object2D&) = default;

    Object2D(Object2D&& other) = default;
    Object2D& operator=(Object2D&& other) = default;
};

Object2D::Object2D(Renderer& render, const Transform& transform, const string& filename):
        tex(render, filename), transform(transform) {}

void Object2D::SetColor(Color color) { tex.SetColorAndAlphaMod(color); }

Object2D::~Object2D() {}

#endif
