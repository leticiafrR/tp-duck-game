#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "Object2D.h"
#include "Vector2D.h"

using SDL2pp::Renderer;
using SDL2pp::Texture;
using std::string;

class Camera {
private:
    Renderer render;

    Vector2D position;

    float size;

    vector<Object2D> sprites;
    void DrawTexture(Texture& tex, const Transform& transform);

public:
    Camera(Renderer render, float size);
    void Render();
    Object2D& CreateObject2D(std::string filename, Transform transform);
    void SetSize();
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
    int screenX = (screenWidth / 2) + (transform.GetPos().x - position.x);
    int screenY = (screenHeight / 2) - (transform.GetPos().y - position.y);

    float screenScale = Vector2D(screenWidth, screenHeight).GetMagnitude() / size;

    render.Copy(tex, NullOpt,
                Rect(screenX - ((sprSize.x / 2) * screenScale),
                     screenY - ((sprSize.y / 2) * screenScale), ((sprSize.x) * screenScale),
                     ((sprSize.y) * screenScale)),
                angle);
}

void Camera::Render() {
    render.Clear();
    for (auto& spr: sprites) {
        Transform transform = spr.GetTransform();
        DrawTexture(spr.GetTexture(), transform);
    }
    render.Present();
}

Camera::~Camera() {}

#endif
