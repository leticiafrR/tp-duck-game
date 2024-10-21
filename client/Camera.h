#ifndef CAMERA_H
#define CAMERA_H

#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "Object2D.h"
#include "Vector2D.h"

class Camera {
private:
    SDL2pp::Renderer render;

    Vector2D position;

    float size;

    std::vector<Object2D> sprites;

public:
    Camera(SDL2pp::Renderer render, float size);
    void Render();
    Object2D& CreateObject2D(Transform transform);
    void SetSize();
    ~Camera();
};

Camera::Camera(SDL2pp::Renderer render, float size): render(std::move(render)), size(size) {}

Object2D& Camera::CreateObject2D(Transform transform = Transform()) {
    sprites.emplace_back(render, transform);
    return sprites.back();
}

void Camera::Render() {
    render.Clear();
    for (auto& spr: sprites) {
        Transform transform = spr.GetTransform();
        Vector2D sprPos = transform.GetPos();
        Vector2D sprSize = transform.GetSize();
        float angle = transform.GetAngle();

        int screenWidth = render.GetOutputWidth();
        int screenHeight = render.GetOutputHeight();
        int screenX = (screenWidth / 2) + (sprPos.x - position.x);
        int screenY = (screenHeight / 2) - (sprPos.y - position.y);

        float screenScale = Vector2D(screenWidth, screenHeight).GetMagnitude() / size;

        render.Copy(spr.GetTexture(), SDL2pp::NullOpt,
                    SDL2pp::Rect(screenX - ((sprSize.x / 2) * screenScale),
                                 screenY - ((sprSize.y / 2) * screenScale),
                                 ((sprSize.x) * screenScale), ((sprSize.y) * screenScale)),
                    angle);
    }
    render.Present();
}

Camera::~Camera() {}

#endif
