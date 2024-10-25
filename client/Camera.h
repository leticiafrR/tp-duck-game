#ifndef CAMERA_H
#define CAMERA_H

#include <algorithm>
#include <list>
#include <string>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "common/Vector2D.h"

#include "Object2D.h"

using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::Texture;
using std::string;

class Camera {
private:
    Renderer render;

    Vector2D position;

    float size;

    std::list<Object2D> sprites;
    void DrawTexture(Texture& tex, const Transform& transform);

public:
    Camera(Renderer render, float size);
    void Render();
    Object2D& CreateObject2D(std::string filename, Transform transform);
    void SetPos(Vector2D position) { this->position = position; }
    Vector2D GetPos() { return position; }
    void SetSize(float size) { this->size = size; }
    float GetSize() { return this->size; }
    ~Camera();
};

Camera::Camera(Renderer render, float size): render(std::move(render)), size(size) {}

Object2D& Camera::CreateObject2D(string filename, Transform transform = Transform()) {
    sprites.emplace_back(render, transform, filename);
    return sprites.back();
}

void Camera::DrawTexture(Texture& tex, const Transform& transform) {
    Vector2D sprSize = transform.GetSize();
    float angle = transform.GetAngle();

    int screenWidth = render.GetOutputWidth();
    int screenHeight = render.GetOutputHeight();

    // float screenScale = Vector2D(screenWidth, screenHeight).GetMagnitude() / size;

    // Mantiene completamente la relación de aspecto
    float screenScale = std::min(static_cast<float>(screenWidth) / size,
                                 static_cast<float>(screenHeight) / size);

    int screenX = (screenWidth / 2) + (transform.GetPos().x - position.x) * screenScale;
    int screenY = (screenHeight / 2) - (transform.GetPos().y - position.y) * screenScale;


    render.Copy(tex, SDL2pp::NullOpt,
                Rect(screenX - ((sprSize.x) * screenScale) / 2,
                     screenY - ((sprSize.y) * screenScale) / 2, ((sprSize.x) * screenScale),
                     ((sprSize.y) * screenScale)),
                angle);
}

void Camera::Render() {
    render.Clear();
    for (auto& spr: sprites) {
        Transform& transform = spr.GetTransform();
        DrawTexture(spr.GetTexture(), transform);
    }
    render.Present();
}

Camera::~Camera() {}

#endif
