#ifndef OBJECT_2D_H
#define OBJECT_2D_H

#include <algorithm>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "common/Transform.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"

using SDL2pp::Color;
using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::Texture;
using std::string;

class Object2D {
protected:
    string filename;
    SDL2pp::Optional<Rect> sourceRect;

    Transform transform;
    Color color = ColorExtension::White();

    bool flipH = false;
    bool visible = true;

public:
    Object2D();
    Object2D(const std::string& filename, const Transform& transform,
             Color color = Color(255, 255, 255, 255));

    void SetColor(Color color);
    Color GetColor();

    Transform& GetTransform();
    void SetTransform(const Transform& transform);

    std::string& GetFileName();
    void SetFileName(const std::string& filename);

    void SetSourceRect(const SDL2pp::Optional<Rect>& rect);
    SDL2pp::Optional<Rect> GetSourceRect();

    void SetFlip(bool flipH);
    bool GetFlip();

    int GetFlipSDL();

    virtual void Draw(Camera& cam);

    void SetVisible(bool visible);

    virtual ~Object2D();

    Object2D(const Object2D&) = default;
    Object2D& operator=(const Object2D&) = default;

    Object2D(Object2D&& other) = default;
    Object2D& operator=(Object2D&& other) = default;
};

#endif
